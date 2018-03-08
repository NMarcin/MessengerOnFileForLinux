#pragma
#include <string>
#include <memory>

#include "LocalUser.hpp"

class SignIn
{
public:
    bool signInUser() const;
    SignIn();
    ~SignIn();

private:
    bool isUserLogged(const LocalUser & user) const;
    bool isPasswordCorrect(const std::string & password, const std::string & correctPassword) const;
    std::unique_ptr< std::string> getPasswordFromDatabase(const LocalUser & user) const;
    bool setUserDataInLoggedFile(const LocalUser & user) const;
    std::string enterThePassword() const;
};
