#pragma once
#include "Logger.hpp"
#include "LogSpace.hpp"

class SignOut
{
public:
    bool signOutUser() const;

    SignOut() = default;
    ~SignOut() = default;

    SignOut(SignOut &&) = delete;
    SignOut operator=(SignOut &&) = delete;
    SignOut(const SignOut &) = delete;
    SignOut operator=(const SignOut &) = delete;

private:
    bool removeUserDataFromLoggedFile() const;

    Logger _log {LogSpace::UserService};
};
