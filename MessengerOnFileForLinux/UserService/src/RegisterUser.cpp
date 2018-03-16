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

    std::cerr << "The passwords are differnet" << std::endl;
    return false;
}


bool RegisterUser::isUserRegistered() const
{
    std::unique_ptr<std::vector<std::string>> registeredFileContent = FileInterface::getFileContent(FILE_::REGISTERED_FILE);

    for (auto & x : *registeredFileContent)
    {
        std::string username = LocalUser::getLocalUser().getUsername();
        std::unique_ptr<std::string> usernameToCompare = std::make_unique<std::string>(*FileInterface::getRowField(x, FileField::usernameFieldInRegisteredFile));

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
        std::array<std::string, 2> passwords = *askUserForPassword();

        if (comparePasswords(passwords))
        {
            isPasswordSetCorrectly = setUserPassword(passwords.front());
        }
    }

    bool isUserDataSavedCorrectly = saveUserDataInRegisteredFile();

    while (!isUserDataSavedCorrectly)
    {
        sleep(1);
        isUserDataSavedCorrectly = saveUserDataInRegisteredFile();
    }

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
    std::string actualDateTime = System::getActualDateTime();
    std::string accountInformations = "[" + LocalUser::getLocalUser().getUsername() + "]["
            + LocalUser::getLocalUser().getPassword() +"]["+ actualDateTime +"]";
    //TODO mwozniak
    //^ tu bedzie jeszcze ta klasa ktora dodaje nawiasy

    return FileInterface::addRow(FILE_::REGISTERED_FILE, accountInformations);
}
