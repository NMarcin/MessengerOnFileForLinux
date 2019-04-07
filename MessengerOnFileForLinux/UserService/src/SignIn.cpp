#include <vector>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <csignal>

#include <LocalUser.hpp>
#include <SHA1.hpp>
#include <SignIn.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <ConsoleWindow.hpp>
#include <StringSum.hpp>
#include "SignalHandling.hpp"

SignIn::SignIn(const InformationPrinter& informationPrinter)
    : _informationPrinter(informationPrinter)
{
    initscr();
    std::signal(SIGWINCH, SignalHandling::NCurses::resizeHandlerInSignInWindow);
    log_.function("SignIn C-TOR");
}

SignIn::~SignIn()
{
    endwin();
    log_.function("SignIn D-TOR");
}

std::string SignIn::enterThePassword() const
{
    log_.function("SignIn::enterThePassword() started");
    ConsoleWindow::displaySignInWindow();

    std::string password;
    std::cin >> password;
    return password;
}

bool SignIn::signInUser() const
{
    log_.function("SignIn::signInUser() started");
    if (isUserLogged())
    {
        log_.info("SignIn::signInUser ERROR: You are already logged in");
        return false;
    }

    std::unique_ptr<std::string> passwordFromDatabase = getPasswordFromDatabase();
    if (nullptr == passwordFromDatabase)
    {
        log_.info("SignIn::signInUser ERROR: You are not registered");
        return false;
    }

    bool isPasswordsEqual = false;
    for (int i = 0; i < 3; i++)
    {
        std::string password = enterThePassword();
        if (isPasswordCorrect(password, *passwordFromDatabase))
        {
            isPasswordsEqual = true;
            break;
        }
    }

    if (!isPasswordsEqual)
    {
        log_.info("SignIn::signInUser() WARNING: Incorrect password");
        return false;
    }

    bool isUserDataSetCorrectly = setUserDataInLoggedFile();
    while (!isUserDataSetCorrectly)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        isUserDataSetCorrectly = setUserDataInLoggedFile();
    }

    log_.info("SignIn::signInUser() SUCCESS");
    return true;
}


bool SignIn::isUserLogged() const
{
    log_.function("SignIn::isUserLogged() started");

    auto userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, LocalUser::getLocalUser().getUsername());
    if(nullptr == userInfo)
    {
        return false;
    }

    log_.info("SignIn::isUserLogged() WARNING: User is already logged");
    return true;
}

bool SignIn::isPasswordCorrect(const std::string& password, const std::string& correctPassword) const
{
    log_.function("SignIn::isPasswordCorrect() started");

    SHA1 hashObject;
    hashObject.update(password);
    if (!hashObject.final().compare(correctPassword)) //0 when succes
    {
        return true;
    }

    ConsoleWindow::displaySignInWindow();
    printw("Incorrect password. Enter password again.");
    refresh();
    sleep(1);

    log_.info("SignIn::isPasswordCorrect WARNING: Incorect password");
    return false;
}

std::unique_ptr<std::string> SignIn::getPasswordFromDatabase() const
{
    log_.function("SignIn::getPasswordFromDatabase() started");

    std::string username = LocalUser::getLocalUser().getUsername();
    auto row = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, username);

    if (row)
    {
        return FileInterface::Accesor::getRowField(*row, FileStructure::RegisteredFile::password);
    }

    log_.info("SignIn::getPasswordFromDatabase ERROR: User does not exist in registered file");
    return nullptr;
}


bool SignIn::setUserDataInLoggedFile() const
{
    log_.function("SignIn::setUserDataInLoggedFile() started");
    std::string user = LocalUser::getLocalUser().getUsername();

    StringSumSquareBrackets information;
    information.sum(user);
    information.sum(UserStatus::activeStatus);

    return FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, information.getSumedString());
}
