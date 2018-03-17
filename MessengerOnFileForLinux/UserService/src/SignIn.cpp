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

    std::unique_ptr<std::string> passwordFromDatabase = std::make_unique<std::string>(*getPasswordFromDatabase());

    if (nullptr == passwordFromDatabase)
    {
        std::cerr << " You are not registered " <<std::endl;
        return false;
    }

    std::string password = enterThePassword();

    if (!isPasswordCorrect(password, *passwordFromDatabase))
    {
        std::cerr << "Incorrect password" << std::endl;
        return false;
    }

    bool isUserDataSetCorrectly = setUserDataInLoggedFile();

    while (!isUserDataSetCorrectly)
    {
        sleep(1);
        isUserDataSetCorrectly = setUserDataInLoggedFile();
    }

    return true;
}


bool SignIn::isUserLogged() const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = std::make_unique<std::vector<std::string>>(*FileInterface::Accesor::getFileContent(FILE_::LOGGED_FILE, FILE_::PATH::LOGGED_PATH));

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::Accesor::getRowField(x, FileField::usernameFieldInLoggedFile));
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
    std::unique_ptr<std::vector<std::string>> registeredFileContent = std::make_unique<std::vector<std::string>>(*FileInterface::Accesor::getFileContent(FILE_::REGISTERED_FILE, FILE_::PATH::REGISTERED_PATH));

    for (auto& x : *registeredFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::Accesor::getRowField(x, FileField::usernameFieldInRegisteredFile));
        std::string username = LocalUser::getLocalUser().getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            return FileInterface::Accesor::getRowField(x, FileField::passwordFieldInRegisteredFile);
        }
    }

    return nullptr;
}


bool SignIn::setUserDataInLoggedFile() const
{
    std::string userPid = std::to_string(LocalUser::getLocalUser().getUserPid());
    std::string information = "[" + LocalUser::getLocalUser().getUsername() + "][" + FileField::FieldValue::userActiveStatus + "][" + userPid +"]";

    return FileInterface::Modification::addRow(FILE_::LOGGED_FILE, FILE_::PATH::LOGGED_PATH, information); //TODO update date&&time in registered file
}
