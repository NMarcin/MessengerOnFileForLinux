#include <SignOut.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>


bool SignOut::signOutUser() const
{
    log_.function("SignOut::signOutUser() started");
    bool isUserSignedOut = removeUserDataFromLoggedFile();
    if(isUserSignedOut)
    {
        return true;
    }

    log_.info("SignOut::removeUserDataFromLoggedFile ERROR: SignOut failed!");
    return false;
}

bool SignOut::removeUserDataFromLoggedFile() const
{
    log_.function("SignOut::removeUserDataFromLoggedFile() started");
    return FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, LocalUser::getLocalUser().getUsername());
}
