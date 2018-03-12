#pragma once
#include <string>

#include <LocalUser.hpp>

class RegisterUser
{
public:
    bool registerNewUser() const;

    RegisterUser();
    ~RegisterUser();

private:
    bool isUserRegistered() const;
    std::string enterThePassword() const;
    bool saveUserDataInRegisteredFile() const;
    bool setUsernamePassword(const std::string & password, const std::string & repeatedPassword) const;
};
