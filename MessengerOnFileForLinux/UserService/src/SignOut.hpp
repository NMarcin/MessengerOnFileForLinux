#pragma once
#include "User.hpp"

class SignOut
{
public:
    bool signOutUser();
    SignOut();
    ~SignOut();

private:
    bool removeUserDataFromLoggedFile(User & user);
};

