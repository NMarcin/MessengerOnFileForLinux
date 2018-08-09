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

bool HistoryDowloander::doCommand() // TODO think about chatHistoryPath, how to get it
{
    std::string systemCommand = "a";//"cp " + TerminalCommand::chatFileWithPath_ + " " + ENVIRONMENT_PATH::TO_FOLDER::USER;
    bool commandStatus = system(systemCommand.c_str());

    return commandStatus;
}
