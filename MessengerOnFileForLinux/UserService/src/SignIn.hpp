#pragma once
#include <memory>

#include "Logger.hpp"
#include "LogSpace.hpp"
#include "NcursesPrintToMainWindowOperationWrapper.hpp"
#include "SignalHandler.hpp"

class SignIn
{
public:
    bool signInUser() const;
    SignIn(const NcursesPrintOperationWrapper&, const SignalHandler& signalHandler);
    ~SignIn();

    SignIn() = delete;
    SignIn(SignIn &&) = delete;
    SignIn operator=(SignIn &&) = delete;
    SignIn(const SignIn &) = delete;
    SignIn operator=(const SignIn &) = delete;

private:
    bool isUserLogged() const;
    bool isPasswordCorrect(const std::string& password, const std::string& correctPassword) const;
    std::unique_ptr<std::string> getPasswordFromDatabase() const;
    bool setUserDataInLoggedFile() const;
    std::string enterThePassword() const;

    const NcursesPrintOperationWrapper& _ncursesPrintOperationWrapper;
    const SignalHandler& _signalHandler;
    Logger _log {LogSpace::UserService};
};
