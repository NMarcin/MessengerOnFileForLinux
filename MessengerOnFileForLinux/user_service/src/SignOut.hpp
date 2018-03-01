#pragma once
#include "User.hpp"

class SignOut
{
public:
    bool signOut();
private:
    bool removeUserDataFromLoggedFile(User & user);
};

