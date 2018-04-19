#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <SHA1.hpp>

RegisterUser::RegisterUser()
{
    log.info("RegisterUser C-TOR");
}

RegisterUser::~RegisterUser()
{
    log.info("RegisterUser D-TOR");
}

std::unique_ptr<std::array<std::string, 2>> RegisterUser::askUserForPassword() const
{
    std::unique_ptr<std::array<std::string, 2>> passwords = std::make_unique<std::array<std::string, 2>>();
    passwords->front() = enterThePassword();
    std::cout << "Enter the password again. ";
    passwords->back() = enterThePassword();

    return passwords;
}

std::string RegisterUser::enterThePassword() const
{
    std::string password;
    std::cout << "Enter the password : ";
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
    std::cerr << "The passwords are differnet" << std::endl;
    return false;
}


bool RegisterUser::isUserRegistered() const
{
    auto userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED_FILE, LocalUser::getLocalUser().getUsername());

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
            + LocalUser::getLocalUser().getPassword() +"]";//TODO DATE&&TIME mwozniak
    //TODO mwozniak
    //^ tu bedzie jeszcze ta klasa ktora dodaje nawiasy

    return FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED_FILE, accountInformations);
}
