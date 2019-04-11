#include "LoggingOut.hpp"
#include "SignOut.hpp"

LoggingOut::LoggingOut(std::string command)
                : TerminalCommand(command)
{
    _log.function("LoggingOut() C-TOR");
}

bool LoggingOut::doCommand()
{
    _log.function("LoggingOut::doCommand() started");
    SignOut signOutLocalUser;
    bool commandStatus = false;
    commandStatus = signOutLocalUser.signOutUser();

    std::string logData = "LoggingOut::doCommand() done as " + std::to_string(commandStatus);
    _log.function(logData);
    exit (EXIT_SUCCESS);
}
