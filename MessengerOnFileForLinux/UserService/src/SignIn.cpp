#include <vector>

#include <SHA1.hpp>
#include <SignIn.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

SignIn::SignIn()
{
    log.info("SignIn C-TOR");
}

SignIn::~SignIn()
{
    log.info("SignIn D-TOR");
}

std::string SignIn::enterThePassword() const
{
    log.info("SignIn::enterThePassword started");
    std::string password;
    std::cout << "Enter the password : ";
    std::cin >> password;
    std::cout << std::endl;

    return password;
}

bool SignIn::signInUser() const
{
    log.info("SignIn::signInUser started");
    if (isUserLogged())
    {
        log.info("SignIn::signInUser ERROR: You are already logged in");
        std::cerr << "You are already logged in !" << std::endl;
        return false;
    }

    std::unique_ptr<std::string> passwordFromDatabase = std::make_unique<std::string>(*getPasswordFromDatabase());

    if (nullptr == passwordFromDatabase)
    {
        log.info("SignIn::signInUser ERROR: You are not registered");
        std::cerr << " You are not registered " <<std::endl;
        return false;
    }

    std::string password = enterThePassword();

    if (!isPasswordCorrect(password, *passwordFromDatabase))
    {
        log.info("SignIn::signInUser ERROR: Incorrect password");
        std::cerr << "Incorrect password" << std::endl;
        return false;
    }

    bool isUserDataSetCorrectly = setUserDataInLoggedFile();

    while (!isUserDataSetCorrectly)
    {
        log.info("SignIn::signInUser ERROR: Waiting for logged file acces");
        sleep(1);
        isUserDataSetCorrectly = setUserDataInLoggedFile();
    }

    log.info("SignIn::signInUser SUCCESS");
    return true;
}


bool SignIn::isUserLogged() const
{
    log.info("SignIn::isUserLogged started");
    std::unique_ptr<std::vector<std::string>>loggedFileContent = std::make_unique<std::vector<std::string>>(*FileInterface::Accesor::getFileContent(ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE));

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile));
        std::string username = LocalUser::getLocalUser().getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            return true;
        }
    }

    log.info("SignIn::isUserLogged User is not logged");
    return false;
}

bool SignIn::isPasswordCorrect(const std::string& password, const std::string& correctPassword) const
{
    log.info("SignIn::isPasswordCorrect started");
    SHA1 hashObject;
    hashObject.update(password);

    if (!hashObject.final().compare(correctPassword)) //0 when succes
    {
        return true;
    }

    log.info("SignIn::isPasswordCorrect ERROR: Incorect password");
    return false;
}

std::unique_ptr<std::string> SignIn::getPasswordFromDatabase() const
{
    log.info("SignIn::getPasswordFromDatabase started");
    std::unique_ptr<std::vector<std::string>> registeredFileContent = std::make_unique<std::vector<std::string>>(*FileInterface::Accesor::getFileContent(ENIVRONMENT_PATH::PATH_TO_FILE::REGISTERED_FILE));

    for (auto& x : *registeredFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInRegisteredFile));
        std::string username = LocalUser::getLocalUser().getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            return FileInterface::Accesor::getRowField(x, FileStructure::FileField::passwordFieldInRegisteredFile);
        }
    }

    log.info("SignIn::getPasswordFromDatabase ERROR: User does not exist in registered file");
    return nullptr;
}


bool SignIn::setUserDataInLoggedFile() const
{
    log.info("SignIn::setUserDataInLoggedFile started");
    std::string userPid = std::to_string(LocalUser::getLocalUser().getUserPid());
    std::string information = "[" + LocalUser::getLocalUser().getUsername() + "][" + FileStructure::FieldValue::userActiveStatus + "][" + userPid +"]";

    return FileInterface::Modification::addRow(ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE, information); //TODO update date&&time in registered file
}
