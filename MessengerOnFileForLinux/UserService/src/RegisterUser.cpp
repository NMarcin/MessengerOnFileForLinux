#include <memory>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <csignal>

#include <RegisterUser.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <SHA1.hpp>
#include <ConsoleWindow.hpp>
#include <StringSum.hpp>
#include "SignalHandling.hpp"

RegisterUser::RegisterUser(const InformationPrinter& informationPrinter)
    : _informationPrinter(informationPrinter)
{
    initscr();
    std::signal(SIGWINCH, SignalHandling::NCurses::resizeHandlerInRegistrationWindow);
    _log.function("RegisterUser C-TOR");
}

RegisterUser::~RegisterUser()
{
    endwin();
    _log.function("RegisterUser D-TOR");
}

std::unique_ptr<std::array<std::string, 2>> RegisterUser::askUserForPassword() const
{
    _log.function("RegisterUser::askUserForPassword() started");
    std::unique_ptr<std::array<std::string, 2>> passwords = std::make_unique<std::array<std::string, 2>>();
    passwords->front() = enterThePassword();
    passwords->back() = enterThePassword();

    return passwords;
}

std::string RegisterUser::enterThePassword() const
{
    _log.function("RegisterUser::enterThePassword() started");
    _informationPrinter.printRegistrationWindow();

    std::string password;
    std::cin >> password;
    return password;
}


bool RegisterUser::comparePasswords(std::array<std::string, 2> passwords) const
{
    _log.function("RegisterUser::comparePasswords() started");
    if(passwords.front() == passwords.back())
    {
        _log.info("RegisterUser::comparePassword() success");
        return true;
    }

    _log.info("RegisterUser::comparePassword() failure");
    _informationPrinter.printRegistrationWindow();
    _informationPrinter.printInformation("The passwords are differnet. Enter passwords one more time.");

    return false;
}


bool RegisterUser::isUserRegistered() const
{
    _log.function("RegisterUser::isUserRegistered() started");
    auto userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, LocalUser::getLocalUser().getUsername());

    if (nullptr == userInfo)
    {
        return false;
    }

    _log.info("RegisterUser::isUserRegistered ERROR: User is registered");
    return true;
}


bool RegisterUser::registerNewUser() const
{
    _log.function("RegisterUser::registerNewUser() started");
    if (isUserRegistered())
    {
        _log.info("RegisterUser::registerNewUser ERROR: You already have an account");
        return false;
    }

    constexpr int numberOfPasswordEntries = 2;
    std::array<std::string, numberOfPasswordEntries> providedPasswords;
    bool isPasswordSetCorrectly = false;
    while (!isPasswordSetCorrectly)
    {
        providedPasswords = *askUserForPassword();

        if (comparePasswords(providedPasswords))
        {
            isPasswordSetCorrectly = setUserPassword(providedPasswords.front());
        }
    }

    bool isUserDataSavedCorrectly = saveUserDataInRegisteredFile(providedPasswords.front());
    while (!isUserDataSavedCorrectly)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        isUserDataSavedCorrectly = saveUserDataInRegisteredFile(providedPasswords.front());
    }

    _log.info("RegisterUser::registerNewUser Registration completed successfully");
    return true;
}

bool RegisterUser::setUserPassword(std::string& password) const
{
    _log.function("RegisterUser::setUserPassword() started");

    SHA1 hashObject;
    hashObject.update(password);
    password = hashObject.final();
    return true;
}

bool RegisterUser::saveUserDataInRegisteredFile(const std::string& password) const
{
    _log.function("RegisterUser::saveUserDataInRegisteredFile() started");

    StringSumSquareBrackets information;
    information.sum(LocalUser::getLocalUser().getUsername());
    information.sum(password);
    return FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, information.getSumedString());
}
