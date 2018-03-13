#include <vector>

#include <SHA1.hpp>
#include <SignIn.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

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
    if (isUserLogged())
    {
        std::cerr << "You are already logged in !" << std::endl;
        return false;
    }

    std::unique_ptr<std::string> passwordFromDatabase = getPasswordFromDatabase();

    if (nullptr == passwordFromDatabase)
    {
        //trzeba sie zastanowic jakby to tutaj zalatwic
        //odpalamy od razu rejestracje czy dajemy mozliwsoc rejestracja/zakonczenie programu?
        std::cerr << " You are not registered " <<std::endl;
        return false;
    }

    std::string password = enterThePassword();

    if (isPasswordCorrect(password, *passwordFromDatabase))
    {
        bool isUserDataSetCorrectly = setUserDataInLoggedFile();

        while (!isUserDataSetCorrectly)
        {
            sleep(1);
            isUserDataSetCorrectly = setUserDataInLoggedFile();
        }

        return true;
    }
    else
    {
        std::cerr << "Incorrect password" << std::endl;
        return false;
    }
}


bool SignIn::isUserLogged() const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::returnFileContent(loggedFile);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = FileInterface::getRowField(x, usernameFieldInLoggedFile);
        std::string username = LocalUser::getLocalUser().getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            return true;
        }
    }

    return false;
}

bool SignIn::isPasswordCorrect(const std::string& password, const std::string& correctPassword) const
{
    SHA1 hashObject;
    hashObject.update(password);

    if (!hashObject.final().compare(correctPassword)) //0 when succes
    {
        return true;
    }

    return false;

}

std::unique_ptr<std::string> SignIn::getPasswordFromDatabase() const
{
    std::unique_ptr<std::vector<std::string>> registeredFileContent = FileInterface::returnFileContent(registeredFile);

    for (auto& x : *registeredFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = FileInterface::getRowField(x, usernameFieldInRegisteredFile);
        std::string username = LocalUser::getLocalUser().getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            return FileInterface::getRowField(x, passwordFieldInRegisteredFile);
        }
    }

    return nullptr;
}


bool SignIn::setUserDataInLoggedFile() const
{
    std::string userPid = std::to_string(LocalUser::getLocalUser().getUserProcessIdFromSystem());
    std::string information = "[" + LocalUser::getLocalUser().getUsername() + "][" + userActiveStatus + "][" + userPid +"]";

    return FileInterface::addRow(loggedFile, information); //TODO update date&&time in registered file
}
