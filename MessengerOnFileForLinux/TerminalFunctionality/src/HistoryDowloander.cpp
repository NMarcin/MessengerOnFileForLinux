#include <HistoryDowloander.hpp>

#include <GlobalVariables.hpp>

HistoryDowloander::HistoryDowloander(std::string command, std::string chatFileWithPath)
                : TerminalCommand(command)
                , chatFileWithPath_(chatFileWithPath)
{
    //NOOP
}

HistoryDowloander::~HistoryDowloander()
{
    //NOOP
}

bool HistoryDowloander::doCommand()
{
    std::string systemCommand = "cp " + chatFileWithPath_ + " " + ENVIRONMENT_PATH::TO_FOLDER::USER;
    bool commandStatus = system(systemCommand.c_str());

    return commandStatus;
}
