#include "SHA1.hpp"
#include "SignIn.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"
#include <vector>

bool SignIn::signIn(std::string password)
{
    User user;

    if (!isUserLogged(user))
    {
        if (isPasswordCorrect(password, *getPasswordFromDatabase(user)))
        {
            return setUserDataInLoggedFile(user);
        }
        else
        {
            std::cerr << "Incorrect password" << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "You are already logged in !" << std::endl;
        return false;
    }
}


bool SignIn::isUserLogged(User & user)
{
    std::unique_ptr< std::vector< std::string>>
            loggedFileContent = returnFileContent(loggedFile);

    for (auto &x : *loggedFileContent)
    {
        if (0 == user.getUsername().compare(*getRowField(x, usernameFieldInLoggedFile)))
           return true;
    }

    return false;
}

bool SignIn::isPasswordCorrect(std::string password, std::string correctPassword)
{
    SHA1 hashObject;
    hashObject.update(password);

    if (0 == hashObject.final().compare(correctPassword))
        return true;
    else
        return false;
}

std::unique_ptr< std::string> SignIn::getPasswordFromDatabase(User & user)
{
    std::unique_ptr< std::vector< std::string>> registeredFileContent = returnFileContent(registeredFile);

    for (auto &x : *registeredFileContent)
    {
        if (0 == user.getUsername().compare(*getRowField(x, usernameFieldInRegisteredFile)))
          return getRowField(x, passwordFieldInRegisteredFile);
    }

    return nullptr; //nie zarejstrowany
}


bool SignIn::setUserDataInLoggedFile(User & user)
{
    std::string information = "[" + user.getUsername() + "][" + userActiveStatus + "]";
    return addRow(loggedFile, information);
}
