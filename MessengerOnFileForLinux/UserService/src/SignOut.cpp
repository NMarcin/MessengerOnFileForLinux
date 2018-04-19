#include <SignOut.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

SignOut::SignOut()
{
    log.info("SignOut C-TOR");
}

SignOut::~SignOut()
{
    log.info("SignOut D-TOR");
}

bool SignOut::signOutUser() const
{
    log.info("SignOut::signOutUser started");
    bool isUserSignedOut = removeUserDataFromLoggedFile();
    if(isUserSignedOut)
    {
        return true;
    }

    log.info("SignOut::removeUserDataFromLoggedFile ERROR: SignOut failed!");
    return false;
}

bool SignOut::removeUserDataFromLoggedFile() const
{
    return FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE, LocalUser::getLocalUser().getUsername());
}
