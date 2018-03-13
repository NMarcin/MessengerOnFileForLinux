#include <memory>
#include <vector>
#include <iostream>

#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <SHA1.hpp>

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

bool RegisterUser::isUserRegistered() const
{
    std::unique_ptr<std::vector<std::string>> registeredFileContent = FileInterface::returnFileContent(registeredFile);

    for (auto & x : *registeredFileContent)
    {
        std::string username = LocalUser::getLocalUser().getUsername();
        std::unique_ptr<std::string> usernameToCompare = FileInterface::getRowField(x, usernameFieldInRegisteredFile);
        //TODO mwozniak
        //Nie da się zrobić tego w jednej lini z make_unique. Trzeba to rozbić tak jak poniżej.
        //To porobić wszedzie tą wersje z make_unique czy zostawić tak jak jest ?
        //std::unique_ptr<std::string> usernameToCompare = std::make_unique<std::string>();
        //usernameToCompare = getRowField(x, usernameFieldInRegisteredFile);

        if (!username.compare(*usernameToCompare)) //0 when the same
        {
            return true;
        }
    }

    return false;
}

bool RegisterUser::registerNewUser() const
{
    if (isUserRegistered())
    {
        std::cerr << "You already have an account" <<std::endl;
        return false;
    }

    bool isPasswordSetCorrectly = false;

    while (!isPasswordSetCorrectly)
    {
        std::string password = enterThePassword();
        std::cout << "Enter the password again. ";
        std::string repeatedPassword = enterThePassword();
        isPasswordSetCorrectly =  setUserPassword(password, repeatedPassword);
    }

    bool isUserDataSavedCorrectly = saveUserDataInRegisteredFile();

    while (!isUserDataSavedCorrectly)
    {
        sleep(1);
        isUserDataSavedCorrectly = saveUserDataInRegisteredFile();
    }

    return true;
}

bool RegisterUser::setUserPassword(const std::string & password, const std::string & repeatedPassword) const
{
    if (password == repeatedPassword)
    {
        SHA1 hashObject;
        hashObject.update(password);
        LocalUser::getLocalUser().setPassword(hashObject.final());
        return true;
    }
    else
    {
        std::cerr << "The passwords are differnet" << std::endl;
        return false;
    }
}

bool RegisterUser::saveUserDataInRegisteredFile() const
{
    std::string actualDateTime = System::getActualDateTime();
    std::string accountInformations = "[" + LocalUser::getLocalUser().getUsername() + "]["
            + LocalUser::getLocalUser().getPassword() +"]["+ actualDateTime +"]";
    //TODO mwozniak
    //^ tu bedzie jeszcze ta klasa ktora dodaje nawiasy

    return FileInterface::addRow(registeredFile, accountInformations);
}
