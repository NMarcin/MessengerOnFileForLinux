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
    return removeUserDataFromLoggedFile();
}


bool SignOut::removeUserDataFromLoggedFile()
{
    return removeRow(loggedFile, LocalUser::getLocalUser().getUsername());
}
