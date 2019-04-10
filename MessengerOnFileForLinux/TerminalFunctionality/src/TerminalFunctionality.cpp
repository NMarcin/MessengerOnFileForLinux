#include <TerminalFunctionality.hpp>


#include <UserCommand.hpp>

#include <HistoryDowloander.hpp>
#include <LoggingOut.hpp>
#include <InviteSender.hpp>
#include <GlobalVariables.hpp>
#include <EndConversation.hpp>
#include <InviteReceiver.hpp>
#include <ConsoleWindow.hpp>
#include <iostream>

namespace
{
bool starts_with(const std::string toFind, const std::string ourString);
}

TerminalFunctionality::TerminalFunctionality(std::string chatFileWithPath, ChatStatus chatStatus)
    : chatFileWithPath_(chatFileWithPath)
    , chatStatus_(chatStatus)
{
    //NOOP
}

bool TerminalFunctionality::runCommand(std::string command, std::shared_ptr<ChatInformation> chatInfo)
{
    log_.function("TerminalFunctionality::runCommand() started");
    log_.function(command);

    if (starts_with(UserCommand::historyDowloander, command) && ChatStatus::conversation == chatStatus_)
    {
        log_.info("TerminalFunctionality::runCommand() historyDowloander command");
        terminalCommand_ = std::make_unique<HistoryDowloander>(command, chatFileWithPath_);
    }
    else if (starts_with(UserCommand::endChat, command) && ChatStatus::conversation == chatStatus_)
    {
         log_.info("TerminalFunctionality::runCommand() endChat command");
         terminalCommand_ = std::make_unique<EndConversation>(command, chatInfo);
    }
    else if (starts_with(UserCommand::logout, command))
    {
        log_.info("TerminalFunctionality::runCommand() logout command");
        terminalCommand_ = std::make_unique<LoggingOut>(command);
    }
    else if (starts_with(UserCommand::inviteUser, command))
    {
        log_.info("TerminalFunctionality::runCommand() invite user");
        terminalCommand_ = std::make_unique<InviteSender>(command, chatInfo);
    }
    else if (starts_with(UserCommand::startConversation, command))
    {
        log_.info("TerminalFunctionality::runCommand() start conversation");
        terminalCommand_ = std::make_unique<InviteReceiver>(command, chatInfo);
    }
    else
    {
        log_.info("TerminalFunctionality::runCommand() command NOT FOUND");
        return false;
    }

    return terminalCommand_->doCommand();
}

namespace
{
// waiting for GCC with C++20 support, function similar to it will be avaible in string class
bool starts_with(const std::string starter, const std::string ourString)
{
    auto iteratorOurString = ourString.begin();
    for(auto letter : starter)
    {
        if(letter == *iteratorOurString)
        {
            iteratorOurString++;
        }
        else
        {
            return false;
        }
    }
    return true;
}
}
