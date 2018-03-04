#include "SignOut.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"

bool SignOut::signOut()
{
    User user;
    return removeUserDataFromLoggedFile(user);
}


bool SignOut::removeUserDataFromLoggedFile(User & user)
{
    return removeRow(loggedFile, user.getUsername());
}
