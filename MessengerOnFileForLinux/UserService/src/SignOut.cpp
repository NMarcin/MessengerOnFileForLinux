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
    return removeUserDataFromLoggedFile();
}

bool SignOut::removeUserDataFromLoggedFile() const
{
    log.info("SignOut::removeUserDataFromLoggedFile started");
    return FileInterface::Modification::removeRow(ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE, LocalUser::getLocalUser().getUsername());
}
