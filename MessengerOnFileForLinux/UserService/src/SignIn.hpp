#pragma
#include <string>
#include <memory>

#include <LocalUser.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class SignIn
{
public:
    bool signInUser() const;
    SignIn();
    ~SignIn();

private:
    bool isUserLogged() const;
    bool isPasswordCorrect(const std::string& password, const std::string& correctPassword) const;
    std::unique_ptr<std::string> getPasswordFromDatabase() const;
    bool setUserDataInLoggedFile() const;
    std::string enterThePassword() const;

    Logger log {LogSpace::UserService};
};
