#include "UserInactivityDetector.hpp"
#include "FileHandling.hpp"

UserInactivityDetector::UserInactivityDetector(const std::string& username)
    : _username(username)
    , _isUserInactiveDetected(false)
{
    _log.function("ChatControl C-TOR ");
}

bool UserInactivityDetector::isUserInactiveDetected() const
{
    return _isUserInactiveDetected;
}

void UserInactivityDetector::detectUserInactivity()
{
    if (isUserInactive())
    {
        _isUserInactiveDetected = true;
    }
}

bool UserInactivityDetector::isUserInactive() const
{
    const std::string command = "ps -u " + _username + " | grep messenger_bin";
    const std::string commandOutput = ConsolControl::getStdoutFromStartedCommand(command);
    return  commandOutput.empty();
}
