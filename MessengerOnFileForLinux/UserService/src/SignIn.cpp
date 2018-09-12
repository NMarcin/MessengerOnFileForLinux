#include <vector>
#include <chrono>
#include <thread>
#include <ncurses.h>

#include <SHA1.hpp>
#include <SignIn.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <ConsoleWindow.hpp>

SignIn::SignIn()
{
    initscr();
    log.info("SignIn C-TOR");
}

SignIn::~SignIn()
{
    endwin();
    log.info("SignIn D-TOR");
}

std::string SignIn::enterThePassword() const
{
    log.info("SignIn::enterThePassword started");
    std::string password;
    ConsoleWindow::displayLoggedWindow();
    printw("Enter the password : ");
    refresh();
    std::cin >> password;

    return password;
}

bool SignIn::signInUser() const
{
    log.info("SignIn::signInUser started");
    if (isUserLogged())
    {
        log.info("SignIn::signInUser ERROR: You are already logged in");
        std::cerr << "You are already logged in !" << std::endl;
        return false;
    }

    std::unique_ptr<std::string> passwordFromDatabase = getPasswordFromDatabase();

    if (nullptr == passwordFromDatabase)
    {
        log.info("SignIn::signInUser ERROR: You are not registered");
        std::cerr << " You are not registered " <<std::endl;
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
        log.info("SignIn::signInUser ERROR: Incorrect password");
        return false;
    }

    bool isUserDataSetCorrectly = setUserDataInLoggedFile();

    while (!isUserDataSetCorrectly)
    {

        std::this_thread::sleep_for(std::chrono::microseconds(500));
        isUserDataSetCorrectly = setUserDataInLoggedFile();
    }

    log.info("SignIn::signInUser SUCCESS");
    return true;
}


bool SignIn::isUserLogged() const
{

    auto userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, LocalUser::getLocalUser().getUsername());

    if(nullptr == userInfo)
    {
        log.info("SignIn::isUserLogged User is not logged");
        return false;
    }

    log.info("SignIn::isUserLogged User is already logged");
    return true;
}

bool SignIn::isPasswordCorrect(const std::string& password, const std::string& correctPassword) const
{
    log.info("SignIn::isPasswordCorrect started");
    SHA1 hashObject;
    hashObject.update(password);

    if (!hashObject.final().compare(correctPassword)) //0 when succes
    {
        return true;
    }

    ConsoleWindow::displayLoggedWindow();
    printw("Incorrect password. Enter password again.");
    refresh();
    sleep(1);

    log.info("SignIn::isPasswordCorrect ERROR: Incorect password");
    return false;
}

std::unique_ptr<std::string> SignIn::getPasswordFromDatabase() const
{
    log.info("SignIn::getPasswordFromDatabase started");

    std::string username = LocalUser::getLocalUser().getUsername();
    auto row = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, username);

    if (row)
    {
        return FileInterface::Accesor::getRowField(*row, FileStructure::RegisteredFile::password);
    }

    log.info("SignIn::getPasswordFromDatabase ERROR: User does not exist in registered file");
    return nullptr;
}


bool SignIn::setUserDataInLoggedFile() const
{
    log.info("SignIn::setUserDataInLoggedFile started");
    std::string information = "[" + LocalUser::getLocalUser().getUsername() + "][" + UserStatus::activeStatus + "]";

    return FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, information); //TODO update date&&time in registered file
}
