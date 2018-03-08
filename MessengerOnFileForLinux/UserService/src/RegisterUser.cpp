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
    return password;
}

bool RegisterUser::isUserRegistered(const LocalUser & user) const
{
    std::unique_ptr< std::vector< std::string>> registeredFileContent = returnFileContent(registeredFile);

    for (auto & x : *registeredFileContent)
    {
        std::string username = user.getUsername();
        std::unique_ptr< const std::string> usernameToCompare = getRowField(x, usernameFieldInRegisteredFile);

        if (!username.compare(*usernameToCompare)) //0 when the same
        {
            return true;
        }
    }

    return false;
}

bool RegisterUser::registerNewUser() const
{

    if (isUserRegistered(LocalUser::getLocalUser()))
    {
        std::cerr << "You already have an account" <<std::endl;
        return false;
    }

    std::string password = enterThePassword();
    std::string repeatedPassword = enterThePassword();

    setUsernamePassword(password, repeatedPassword, LocalUser::getLocalUser());

    return saveUserDataInRegisteredFile(LocalUser::getLocalUser());
}

void RegisterUser::setUsernamePassword(const std::string & password, const std::string & repeatedPassword, LocalUser & user) const
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

bool RegisterUser::saveUserDataInRegisteredFile(LocalUser & user) const
{
    std::string actualDateTime = getActualDateTime();
    std::string accountInformations = "[" + user.getUsername() + "][" //tu bedzie jeszcze ta funkcja ktora dodaje nawiasy
            + user.getPassword() +"]["+ actualDateTime +"]";

    return addRow(registeredFile, accountInformations);
}

