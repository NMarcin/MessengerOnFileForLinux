#include <vector>

#include "SHA1.hpp"
#include "SignIn.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"

SignIn::SignIn()
{
    //NOOP
}

SignIn::~SignIn()
{
    //NOOP
}

std::string SignIn::enterThePassword() const
{
    std::string password;
    std::cout << "Enter the password : ";
    std::cin >> password;
    std::cout << std::endl;
    return password;
}

bool SignIn::signInUser() const
{
    if (isUserLogged(LocalUser::getLocalUser()))
    {
        std::cerr << "You are already logged in !" << std::endl;
        return false;
    }

    std::string password = enterThePassword();
    std::unique_ptr< std::string> passwordFromDatabase = getPasswordFromDatabase(LocalUser::getLocalUser());

    if (isPasswordCorrect(password, *passwordFromDatabase))
    {
        return setUserDataInLoggedFile(LocalUser::getLocalUser());
    }
    else
    {
        std::cerr << "Incorrect password" << std::endl;
        return false;
    }
}


bool SignIn::isUserLogged(const LocalUser & user) const
{
    std::unique_ptr< std::vector< std::string>>loggedFileContent = returnFileContent(loggedFile);

    for (auto &x : *loggedFileContent)
    {
        std::unique_ptr< const std::string> usernameToComapre = getRowField(x, usernameFieldInLoggedFile);

        if (!user.getUsername().compare(*usernameToComapre)) //0 when succes
        {
            return true;
        }
    }

    return false;
}

bool SignIn::isPasswordCorrect(const std::string & password, const std::string & correctPassword) const
{
    SHA1 hashObject;
    hashObject.update(password);

    if (0 == hashObject.final().compare(correctPassword))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::unique_ptr< std::string> SignIn::getPasswordFromDatabase(const LocalUser & user) const
{
    std::unique_ptr< std::vector< std::string>> registeredFileContent = returnFileContent(registeredFile);

    for (auto &x : *registeredFileContent)
    {
        std::unique_ptr< std::string> usernameToComapre = getRowField(x, usernameFieldInRegisteredFile);

        if (0 == user.getUsername().compare(*usernameToComapre))
            return getRowField(x, passwordFieldInRegisteredFile);
    }

    std::cerr << " You are not registered " <<std::endl;
    return nullptr;
}


bool SignIn::setUserDataInLoggedFile(const LocalUser & user) const
{
    std::string userPid = std::to_string(user.getUserProcessIdFromSystem());
    std::string information = "[" + user.getUsername() + "][" + userActiveStatus + "][" + userPid +"]";
    return addRow(loggedFile, information); //TODO update date&&time in registered file
}
