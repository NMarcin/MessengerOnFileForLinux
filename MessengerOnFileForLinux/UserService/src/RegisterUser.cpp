#include <SHA1.hpp>
#include <memory>
#include <vector>
#include <iostream>

#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

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
    std::unique_ptr<std::vector<std::string>> registeredFileContent = returnFileContent(registeredFile);

    for (auto & x : *registeredFileContent)
    {
        std::string username = LocalUser::getLocalUser().getUsername();
        std::unique_ptr<std::string> usernameToCompare = getRowField(x, usernameFieldInRegisteredFile);
        //TODO
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
        isPasswordSetCorrectly =  setUsernamePassword(password, repeatedPassword);
    }

    bool isUserDataSavedCorrectly = saveUserDataInRegisteredFile();

    while (!isUserDataSavedCorrectly)
    {
        //czekamy az zwolni sie plik. Dac jakiegos sleepa moze ?
        isUserDataSavedCorrectly = saveUserDataInRegisteredFile();
    }

    return true;
}

bool RegisterUser::setUsernamePassword(const std::string & password, const std::string & repeatedPassword) const
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
    std::string actualDateTime = getActualDateTime();
    std::string accountInformations = "[" + LocalUser::getLocalUser().getUsername() + "]["
            + LocalUser::getLocalUser().getPassword() +"]["+ actualDateTime +"]";
    //^ tu bedzie jeszcze ta klasa ktora dodaje nawiasy

    return addRow(registeredFile, accountInformations);
}
