#include <HistoryDowloander.hpp>

#include <GlobalVariables.hpp>

HistoryDowloander::HistoryDowloander(std::string command)
                : TerminalCommand(command)
{
    //NOOP
}

HistoryDowloander::~HistoryDowloander()
{
    //NOOP
}

bool HistoryDowloander::doCommand() // TODO think about chatHistoryPath, how to get it
{
    std::string chatHistoryPath = "home/messenger/chats/0mnurzyns_mwozniak/mnurzyns_mwozniak";
    std::string systemCommand = "cp " + chatHistoryPath + " " + ENIVRONMENT_PATH::PATH_TO_FOLDER::USER_FOLDER;
    bool commandStatus = system(systemCommand.c_str());

    return commandStatus;
}
