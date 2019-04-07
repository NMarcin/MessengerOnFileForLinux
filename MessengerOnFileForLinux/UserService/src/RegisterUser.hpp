#pragma once
#include <memory>

#include <Logger.hpp>
#include <LogSpace.hpp>
#include "InformationPrinter.hpp"

class RegisterUser
{
public:
    bool registerNewUser() const;

    RegisterUser(const InformationPrinter&);
    ~RegisterUser();

    RegisterUser() = delete;
    RegisterUser(RegisterUser &&) = delete;
    RegisterUser operator=(RegisterUser &&) = delete;
    RegisterUser(const RegisterUser &) = delete;
    RegisterUser operator=(const RegisterUser &) = delete;

private:
    std::unique_ptr<std::array<std::string, 2>> askUserForPassword() const;
    bool comparePasswords(std::array<std::string, 2> passwords) const;
    bool isUserRegistered() const;
    std::string enterThePassword() const;
    bool saveUserDataInRegisteredFile(const std::string& password) const;
    bool setUserPassword(std::string& password) const;

    const InformationPrinter& _informationPrinter;

    Logger _log {LogSpace::UserService};
};
