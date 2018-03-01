#pragma once
#include "RegisterUser.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"
#include <SHA1.hpp>
#include <memory>
#include <vector>
#include <iostream>


bool RegisterUser::isUserRegistered(std::string username)
{
    std::unique_ptr< std::vector< std::string>>
            registeredFileContent = returnFileContent(registeredFile); //testing file
    static constexpr int usernameField = 0;
    for (auto &x : *registeredFileContent)
    {
        if (0 == username.compare(*getRowField(x, usernameField)))
            return true;
    }
    return false;
}

bool RegisterUser::registerUser(std::string password, std::string repeatedPassword)
{
    User user;
    if (!isUserRegistered(user.getUsername()))
    {
        setUsernamePassword(password, repeatedPassword, user);
        return saveUserDataInRegisteredFile(user);
    }
    else
        return false; //uzytkownik istnieje
}

void RegisterUser::setUsernamePassword(std::string password, std::string repeatedPassword, User & user)
{
    if (password == repeatedPassword)
    {
        SHA1 hashObject;
        hashObject.update(password);
        user.setPassword(hashObject.final());
    }
    else
    {
        //error hasla nie pasuja
    }
}

bool RegisterUser::saveUserDataInRegisteredFile(const User & user)
{
    std::string accountInformations = "[" + user.getUsername() + "]["
                                    + user.getPassword() +"]["+ getActualDateTime() +"]";

    return addRow(registeredFile, accountInformations);
}

