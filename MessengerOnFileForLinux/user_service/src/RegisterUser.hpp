#pragma once
#include <string>

#include "User.hpp"

class RegisterUser
{
public:
    bool registerNewUser() const;
    RegisterUser();
    ~RegisterUser();

private:
    bool isUserRegistered(const std::string & username) const;
    bool saveUserDataInRegisteredFile(User & user) const;
    void setUsernamePassword(const std::string & password, const std::string & repeatedPassword, User & user) const;
    std::string enterThePassword() const;
};
