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
    User user;

    if (!isUserLogged(user.getUsername()))
    {
        std::cerr << "You are already logged in !" << std::endl;
        return false;
    }

    std::string password = enterThePassword();
    std::string passwordFromDatabase = *getPasswordFromDatabase(user);

    if (isPasswordCorrect(password, passwordFromDatabase))
    {
        return setUserDataInLoggedFile(user);
    }
    else
    {
        std::cerr << "Incorrect password" << std::endl;
        return false;
    }
}


bool SignIn::isUserLogged(const std::string & username) const
{
    std::unique_ptr< std::vector< std::string>>loggedFileContent = returnFileContent(loggedFile);

    for (auto &x : *loggedFileContent)
    {
        std::string usernameToComapre = *getRowField(x, usernameFieldInLoggedFile);

        if (0 == username.compare(usernameToComapre))
            return true;
    }

    return false;
}

bool SignIn::isPasswordCorrect(const std::string & password, const std::string & correctPassword) const
{
    SHA1 hashObject;
    hashObject.update(password);

    if (0 == hashObject.final().compare(correctPassword))
        return true;
    else
        return false;
}

std::unique_ptr< std::string> SignIn::getPasswordFromDatabase(User & user) const
{
    std::unique_ptr< std::vector< std::string>> registeredFileContent = returnFileContent(registeredFile);

    for (auto &x : *registeredFileContent)
    {
        if (0 == user.getUsername().compare(*getRowField(x, usernameFieldInRegisteredFile)))
            return getRowField(x, passwordFieldInRegisteredFile);
    }

    std::cerr << " You are not registered " <<std::endl;
    return nullptr;
}


bool SignIn::setUserDataInLoggedFile(User & user) const
{
    std::string information = "[" + user.getUsername() + "][" + userActiveStatus + "]";
    return addRow(loggedFile, information); //TODO update date&&time in registered file
}
