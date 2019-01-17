#pragma once
#include <memory>

#include <Logger.hpp>
#include <LogSpace.hpp>

class RegisterUser
{
public:
    bool registerNewUser() const;

    RegisterUser();
    ~RegisterUser();

public:
    std::unique_ptr<std::array<std::string, 2>> askUserForPassword() const;
    bool comparePasswords(std::array<std::string, 2> passwords) const;
    bool isUserRegistered() const;
    virtual std::string enterThePassword() const;
    bool saveUserDataInRegisteredFile() const;
    bool setUserPassword(const std::string & password) const;

    Logger log_ {LogSpace::UserService};
};
