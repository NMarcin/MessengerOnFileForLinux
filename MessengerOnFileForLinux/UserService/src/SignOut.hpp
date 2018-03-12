#pragma once
#include <LocalUser.hpp>

class SignOut
{
public:
    bool signOutUser() const;

    SignOut();
    ~SignOut();

private:
    bool removeUserDataFromLoggedFile() const;
};

