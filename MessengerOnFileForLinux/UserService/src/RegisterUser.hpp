#pragma once
#include <memory>

#include "Logger.hpp"
#include "LogSpace.hpp"
#include "NcursesPrintToMainWindowOperationWrapper.hpp"
#include "SignalHandling.hpp"

class RegisterUser
{
public:
    bool registerNewUser() const;

    RegisterUser(const NcursesPrintOperationWrapper&, const SignalHandler&);
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

    const NcursesPrintOperationWrapper& _ncursesPrintOperationWrapper;
    const SignalHandler& _signalHandler;

    Logger _log {LogSpace::UserService};
};
