#pragma once
#include <LocalUser.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class SignOut
{
public:
    bool signOutUser() const;

    SignOut();
    ~SignOut();

private:
    bool removeUserDataFromLoggedFile() const;

    Logger log {LogSpace::UserService};
};

