#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <stdio.h>

#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <SHA1.hpp>
#include <Display.hpp>

RegisterUser::RegisterUser()
{
    initscr();
    log.info("RegisterUser C-TOR");
}

RegisterUser::~RegisterUser()
{
    endwin();
    log.info("RegisterUser D-TOR");
}

std::unique_ptr<std::array<std::string, 2>> RegisterUser::askUserForPassword() const
{
    std::unique_ptr<std::array<std::string, 2>> passwords = std::make_unique<std::array<std::string, 2>>();
    passwords->front() = enterThePassword();
    Display::displayRegistrationMainWindow();
    printw("Enter the password again. ");
    refresh();
    sleep(1);
    passwords->back() = enterThePassword();

    return passwords;
}

std::string RegisterUser::enterThePassword() const
{
    std::string password;
    Display::displayRegistrationMainWindow();
    printw("Enter the password : ");
    refresh();
    std::cin >> password;
    return password;
}


bool RegisterUser::comparePasswords(std::array<std::string, 2> passwords) const
{
    if(passwords.front() == passwords.back())
    {
        return true;
    }

    log.info("RegisterUser::comparePassword ERROR: Passwords are differnet");
    Display::displayRegistrationMainWindow();
    printw("The passwords are differnet. Enter passwords one more time.");
    refresh();
    sleep(1);
    return false;
}


bool RegisterUser::isUserRegistered() const
{
    auto userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, LocalUser::getLocalUser().getUsername());

    if (nullptr == userInfo)
    {
        return false;
    }

    log.info("RegisterUser::isUserRegistered ERROR: User is registered");
    return true;
}


bool RegisterUser::registerNewUser() const
{
    log.info("RegisterUser::registerNewUser started");
    if (isUserRegistered())
    {
        std::cerr << "You already have an account" <<std::endl;
        log.info("RegisterUser::registerNewUser ERROR: You already have an account");
        return false;
    }


    bool isPasswordSetCorrectly = false;

    while (!isPasswordSetCorrectly)
    {
        std::array<std::string, 2> passwords = *askUserForPassword();

        if (comparePasswords(passwords))
        {
            isPasswordSetCorrectly = setUserPassword(passwords.front());
        }
    }
    std::cerr <<"DUUPA" << std::endl;
    bool isUserDataSavedCorrectly = saveUserDataInRegisteredFile();

    while (!isUserDataSavedCorrectly)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        isUserDataSavedCorrectly = saveUserDataInRegisteredFile();
    }

    log.info("RegisterUser::registerNewUser Registration completed successfully");
    return true;
}

bool RegisterUser::setUserPassword(const std::string& password) const
{
    SHA1 hashObject;
    hashObject.update(password);
    LocalUser::getLocalUser().setPassword(hashObject.final());

    return true;
}

bool RegisterUser::saveUserDataInRegisteredFile() const
{
    std::string accountInformations = "[" + LocalUser::getLocalUser().getUsername() + "]["
            + LocalUser::getLocalUser().getPassword() +"]";
    //TODO mwozniak klasa obsługująca [ ] jeesli sie na nia zdecydujemy
    //Co z czasem zalogowania ?

    return FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, accountInformations);
}
