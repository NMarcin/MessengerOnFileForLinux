#include "SignOut.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"

SignOut::SignOut()
{
    //NOOP
}

SignOut::~SignOut()
{
    //NOOP
}

bool SignOut::signOutUser()
{
    User user;
    return removeUserDataFromLoggedFile(user);
}


bool SignOut::removeUserDataFromLoggedFile(User & user)
{
    return removeRow(loggedFile, user.getUsername());
}
