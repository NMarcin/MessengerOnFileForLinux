#pragma once
#include <string>
#include <memory>

#include <LocalUser.hpp>

class RegisterUser
{
public:
    bool registerNewUser() const;

    RegisterUser();
    ~RegisterUser();

private:
    std::unique_ptr<std::array<std::string, 2>> askUserForPassword() const;
    bool comparePasswords(std::array<std::string, 2> passwords) const;
    bool isUserRegistered() const;
    std::string enterThePassword() const;
    bool saveUserDataInRegisteredFile() const;
    bool setUserPassword(const std::string & password) const;
};
