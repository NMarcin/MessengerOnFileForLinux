#include <LoggingOut.hpp>

#include <SignOut.hpp>

LoggingOut::LoggingOut(std::string command)
                : TerminalCommand(command)
{
    //NOOP
}

LoggingOut::~LoggingOut()
{
    //NOOP
}

bool LoggingOut::doCommand() // TODO think about chatHistoryPath, how to get it
{
    SignOut signOutLocalUser;
    bool commandStatus = false;
    commandStatus = signOutLocalUser.signOutUser();
    return commandStatus;
}
