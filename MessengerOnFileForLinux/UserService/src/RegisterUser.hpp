#pragma once
#include <string>

#include "LocalUser.hpp"

class RegisterUser
{
public:
    bool registerNewUser() const;
    RegisterUser();
    ~RegisterUser();

private:
    bool isUserRegistered(const LocalUser & user) const;
    std::string enterThePassword() const;
    bool saveUserDataInRegisteredFile(LocalUser & user) const;
    void setUsernamePassword(const std::string & password, const std::string & repeatedPassword, LocalUser & user) const;
};
