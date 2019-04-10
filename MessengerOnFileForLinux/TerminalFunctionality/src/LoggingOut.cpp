#include <LoggingOut.hpp>
#include <SignOut.hpp>

LoggingOut::LoggingOut(std::string command)
    : TerminalCommand(command)
{
    log_.function("LoggingOut() C-TOR");
}

bool LoggingOut::doCommand() const
{
    log_.function("LoggingOut::doCommand() started");
    SignOut signOutLocalUser;
    bool commandStatus = false;
    commandStatus = signOutLocalUser.signOutUser();

    std::string logData = "LoggingOut::doCommand() done as " + std::to_string(commandStatus);
    log_.function(logData);
    exit (EXIT_SUCCESS);
}
