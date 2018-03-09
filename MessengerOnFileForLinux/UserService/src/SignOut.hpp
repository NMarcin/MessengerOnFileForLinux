#pragma once
#include "LocalUser.hpp"

class SignOut
{
public:
    bool signOutUser();
    SignOut();
    ~SignOut();

private:
    bool removeUserDataFromLoggedFile();
};

