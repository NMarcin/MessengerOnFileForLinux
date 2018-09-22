#include <HistoryDowloander.hpp>

#include <GlobalVariables.hpp>

HistoryDowloander::HistoryDowloander(std::string command, std::string chatFileWithPath)
                : TerminalCommand(command)
                , chatFileWithPath_(chatFileWithPath)
{
    //NOOP
}

bool HistoryDowloander::doCommand()
{
    log_.function("HistoryDowloander::doCommand()");
    std::string systemCommand = "cp " + chatFileWithPath_ + " " + ENVIRONMENT_PATH::TO_FOLDER::USER;
    bool commandStatus = system(systemCommand.c_str());

    std::string logData = "HistoryDowloander::doCommand() done as " + commandStatus;
    log_.function(logData);
    return commandStatus;
}
