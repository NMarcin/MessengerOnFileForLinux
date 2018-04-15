#include <memory>
#include <vector>
#include <iostream>

#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <SHA1.hpp>

RegisterUser::RegisterUser()
{
    log.info("RegisterUser C-TOR");
}

RegisterUser::~RegisterUser()
{
    log.info("RegisterUser D-TOR");
}

std::unique_ptr<std::array<std::string, 2>> RegisterUser::askUserForPassword() const
{ // TODO mwozniak 5 iteracji pytania o haslo
    log.info("RegisterUser::askUserForPassword started");
    std::unique_ptr<std::array<std::string, 2>> passwords = std::make_unique<std::array<std::string, 2>>();
    passwords->front() = enterThePassword();
    std::cout << "Enter the password again. ";
    passwords->back() = enterThePassword();

    return passwords;
}

std::string RegisterUser::enterThePassword() const
{
    log.info("RegisterUser::enterThePassword started");
    std::string password;
    std::cout << "Enter the password : ";
    std::cin >> password;
    return password;
}


bool RegisterUser::comparePasswords(std::array<std::string, 2> passwords) const
{
    log.info("RegisterUser::comparePassword started");
    if(passwords.front() == passwords.back())
    {
        log.info("RegisterUser::comparePassword Passwords equal");
        return true;
    }

    log.info("RegisterUser::comparePassword ERROR: Passwords are differnet");
    std::cerr << "The passwords are differnet" << std::endl;
    return false;
}


bool RegisterUser::isUserRegistered() const
{
    log.info("RegisterUser::isUserRegistered started");
    std::unique_ptr<std::vector<std::string>> registeredFileContent = FileInterface::Accesor::getFileContent(ENVIRONMENT_PATH::TO_FILE::REGISTERED_FILE);
    if (nullptr == registeredFileContent)
    {
        return true; //error file is empty or can't get acces. May wait for acces ?
    }

    for (auto  x : *registeredFileContent)
    {
        std::string username = LocalUser::getLocalUser().getUsername();
        std::unique_ptr<std::string> usernameToCompare = std::make_unique<std::string>(*FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInRegisteredFile));

        if (!username.compare(*usernameToCompare)) //0 when the same
        {
            log.info("RegisterUser::isUserRegistered User is registered");
            return true;
        }
    }

    log.info("RegisterUser::isUserRegistered ERROR: User does not exist in registered file");
    return false;
}


bool RegisterUser::registerNewUser() const
{
    log.info("RegisterUser::registerNewUser started");
    if (isUserRegistered())
    {
        std::cerr << "You already have an account" <<std::endl;
        log.info("RegisterUser::registerNewUser ERROR: You already have an account");
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
        log.info("RegisterUser::registerNewUser Waiting for registered file access");
        sleep(1);
        isUserDataSavedCorrectly = saveUserDataInRegisteredFile();
    }

    return true;
}

bool RegisterUser::setUserPassword(const std::string& password) const
{
    log.info("RegisterUser::setUserPassword started");
    SHA1 hashObject;
    hashObject.update(password);
    LocalUser::getLocalUser().setPassword(hashObject.final());

    return true;
}

bool RegisterUser::saveUserDataInRegisteredFile() const
{
    log.info("RegisterUser::saveUserDataInRegisteredFile started");
    std::string accountInformations = "[" + LocalUser::getLocalUser().getUsername() + "]["
            + LocalUser::getLocalUser().getPassword() +"]";//TODO DATE&&TIME mwozniak
    //TODO mwozniak
    //^ tu bedzie jeszcze ta klasa ktora dodaje nawiasy

    return FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED_FILE, accountInformations);
}
