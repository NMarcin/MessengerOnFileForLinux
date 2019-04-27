#include <vector>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <csignal>

#include "SHA1.hpp"
#include "SignIn.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"
#include "ConsoleWindow.hpp"
#include "StringSum.hpp"

SignIn::SignIn(const NcursesPrintOperationWrapper& ncursesPrintOperationWrapper,
               const SignalHandler& signalHandler)
    : _ncursesPrintOperationWrapper(ncursesPrintOperationWrapper)
    , _signalHandler(signalHandler)
{
    initscr();
    std::signal(SIGWINCH, signalHandler.terminalResizeHandlerInSignInWindow);
    _log.function("SignIn C-TOR");
}

SignIn::~SignIn()
{
    endwin();
    _log.function("SignIn D-TOR");
}

std::string SignIn::enterThePassword() const
{
    _log.function("SignIn::enterThePassword() started");
    _ncursesPrintOperationWrapper.printSignInWindow();

    std::string password;
    std::cin >> password;
    return password;
}

bool SignIn::signInUser() const
{
    _log.function("SignIn::signInUser() started");
    if (isUserLogged())
    {
        _log.info("SignIn::signInUser ERROR: You are already logged in");
        return false;
    }

    std::unique_ptr<std::string> passwordFromDatabase = getPasswordFromDatabase();
    if (nullptr == passwordFromDatabase)
    {
        _log.info("SignIn::signInUser ERROR: You are not registered");
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
        _log.info("SignIn::signInUser() WARNING: Incorrect password");
        return false;
    }

    bool isUserDataSetCorrectly = setUserDataInLoggedFile();
    while (!isUserDataSetCorrectly)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        isUserDataSetCorrectly = setUserDataInLoggedFile();
    }

    _log.info("SignIn::signInUser() SUCCESS");
    return true;
}


bool SignIn::isUserLogged() const
{
    _log.function("SignIn::isUserLogged() started");

    auto userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, LOCAL_USER);
    if(nullptr == userInfo)
    {
        return false;
    }

    _log.info("SignIn::isUserLogged() WARNING: User is already logged");
    return true;
}

bool SignIn::isPasswordCorrect(const std::string& password, const std::string& correctPassword) const
{
    _log.function("SignIn::isPasswordCorrect() started");

    SHA1 hashObject;
    hashObject.update(password);
    if (!hashObject.final().compare(correctPassword)) //0 when succes
    {
        return true;
    }

    _ncursesPrintOperationWrapper.printSignInWindow();
    _ncursesPrintOperationWrapper.printInformationIntoMainWindow("Incorrect password. Enter password again.");

    _log.info("SignIn::isPasswordCorrect WARNING: Incorect password");
    return false;
}

std::unique_ptr<std::string> SignIn::getPasswordFromDatabase() const
{
    _log.function("SignIn::getPasswordFromDatabase() started");

    std::string username = LOCAL_USER;
    auto row = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, username);

    if (row)
    {
        return FileInterface::Accesor::getRowField(*row, FileStructure::RegisteredFile::password);
    }

    _log.info("SignIn::getPasswordFromDatabase ERROR: User does not exist in registered file");
    return nullptr;
}


bool SignIn::setUserDataInLoggedFile() const
{
    _log.function("SignIn::setUserDataInLoggedFile() started");
    std::string user = LOCAL_USER;

    StringSumSquareBrackets information;
    information.sum(user);
    information.sum(UserStatus::activeStatus);

    return FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, information.getSumedString());
}
