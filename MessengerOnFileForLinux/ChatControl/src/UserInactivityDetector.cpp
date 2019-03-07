#include "UserInactivityDetector.hpp"
#include "FileHandling.hpp"

UserInactivityDetector::UserInactivityDetector(const std::string& username)
    : username_(username)
    , isUserInactiveDetected_(false)
{
    log_.function("ChatControl C-TOR ");
}

bool UserInactivityDetector::isUserInactiveDetected() const
{
    return isUserInactiveDetected_;
}

void UserInactivityDetector::detectUserInactivity()
{
    if (isUserInactive())
    {
        isUserInactiveDetected_ = true;
    }
}

bool UserInactivityDetector::isUserInactive() const
{
    const std::string command = "ps -u " + username_ + " | grep messenger_bin";
    const std::string commandOutput = ConsolControl::getStdoutFromStartedCommand(command);
    return  commandOutput.empty();
}
