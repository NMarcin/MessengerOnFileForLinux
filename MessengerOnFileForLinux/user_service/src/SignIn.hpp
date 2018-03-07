#pragma
#include <string>
#include <memory>

#include "User.hpp"

class SignIn
{
public:
    bool signInUser() const;
    SignIn();
    ~SignIn();

private:
    bool isUserLogged(const std::string & username) const;
    bool isPasswordCorrect(const std::string & password, const std::string & correctPassword) const;
    std::unique_ptr< std::string> getPasswordFromDatabase(User & user) const;
    bool setUserDataInLoggedFile(User & user) const;
    std::string enterThePassword() const;
};
