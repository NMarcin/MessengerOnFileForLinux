#include "HistoryDowloander.hpp"
#include "GlobalVariables.hpp"

HistoryDowloander::HistoryDowloander(std::string command, std::string chatFileWithPath)
                : TerminalCommand(command)
                , _chatFileWithPath(chatFileWithPath)
{
    _log.function("HistoryDowloander() C-TOR");
}

bool HistoryDowloander::doCommand()
{
    _log.function("HistoryDowloander::doCommand()");
    std::string systemCommand = "cp " + _chatFileWithPath + " " + ENVIRONMENT_PATH::TO_FOLDER::USER;
    bool commandStatus = system(systemCommand.c_str());

    std::string logData = "HistoryDowloander::doCommand() done as " + std::to_string(commandStatus);
    _log.function(logData);
    return commandStatus;
}
