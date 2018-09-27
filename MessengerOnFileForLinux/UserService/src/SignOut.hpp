#pragma once
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

    Logger log_ {LogSpace::UserService};
};

