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
    return FileInterface::Modification::removeRow(ENIVRONMENTAL_PATH::PATH_TO_FILE::LOGGED_FILE, LocalUser::getLocalUser().getUsername());
}
