#include <SignOut.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

SignOut::SignOut()
{
    //NOOP
}

SignOut::~SignOut()
{
    //NOOP
}

bool SignOut::signOutUser() const
{
    return removeUserDataFromLoggedFile();
}

bool SignOut::removeUserDataFromLoggedFile() const
{
    return FileInterface::removeRow(loggedFile, LocalUser::getLocalUser().getUsername());
}
