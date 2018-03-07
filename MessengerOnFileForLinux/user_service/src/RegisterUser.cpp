#pragma once
#include <SHA1.hpp>
#include <memory>
#include <vector>
#include <iostream>

#include "RegisterUser.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"

RegisterUser::RegisterUser()
{
    //NOOP
}

RegisterUser::~RegisterUser()
{
    //NOOP
}

std::string RegisterUser::enterThePassword() const
{
    std::string password;
    std::cout << "Enter the password : ";
    std::cin >> password;
    std::cout << std::endl;
    return password;
}

bool RegisterUser::isUserRegistered(const std::string & username) const
{
    std::unique_ptr< std::vector< std::string>> registeredFileContent = returnFileContent(registeredFile);

    for (auto & x : *registeredFileContent)
    {
        std::string usernameToCompare = *getRowField(x, usernameFieldInRegisteredFile);

        if (!username.compare(usernameToCompare)) //0 when the same
            return true;
    }
    return false;
}

bool RegisterUser::registerNewUser() const
{
    User user;

    if (isUserRegistered(user.getUsername()))
    {
        return false; //uzytkownik istnieje
    }

    std::string password = enterThePassword();
    std::string repeatedPassword = enterThePassword();
    setUsernamePassword(password, repeatedPassword, user);

    return saveUserDataInRegisteredFile(user);
}

void RegisterUser::setUsernamePassword(const std::string & password, const std::string & repeatedPassword, User & user) const
{
    if (password == repeatedPassword)
    {
        SHA1 hashObject;
        hashObject.update(password);
        user.setPassword(hashObject.final());
    }
    else
    {
        std::cerr << "The passwords are differnet" << std::endl;
    }
}

bool RegisterUser::saveUserDataInRegisteredFile(User & user) const
{
    std::string actualDateTime = getActualDateTime();
    std::string accountInformations = "[" + user.getUsername() + "]["
            + user.getPassword() +"]["+ actualDateTime +"]";

    bool isRawWasAdded = addRow(registeredFile, accountInformations);
    return isRawWasAdded;
    //turn addRow(registeredFile, accountInformations);
}

