#include <TerminalFunctionality.hpp>


#include <UserCommand.hpp>

#include <HistoryDowloander.hpp>
#include <LoggingOut.hpp>
#include <InviteSender.hpp>
#include <GlobalVariables.hpp>
#include <EndConversation.hpp>
#include <ConsoleWindow.hpp>
#include <iostream>



bool starts_with(const std::string toFind, const std::string ourString);

bool TerminalFunctionality::runCommand(std::string command, std::shared_ptr<ChatInformation> chatInfo)
{
    log_.function("TerminalFunctionality::runCommand()");
    log_.function(command);
    if (starts_with(UserCommand::historyDowloander, command) && ChatStatus::conversation == chatStatus_)
    {
        log_.info("TerminalFunctionality::runCommand() historyDowloander command");
        terminalCommand_ = std::make_unique<HistoryDowloander>(command, chatFileWithPath_);
    }
    else if (starts_with(UserCommand::endChat, command) && ChatStatus::conversation == chatStatus_)
    {
         log_.info("TerminalFunctionality::runCommand() endChat command");
         terminalCommand_ = std::make_unique<EndConversation>(command);
    }
    else if (starts_with(UserCommand::logout, command))
    {
        log_.info("TerminalFunctionality::runCommand() logout command");
        terminalCommand_ = std::make_unique<LoggingOut>(command);
    }
    else if (starts_with(UserCommand::inviteUser, command))
    {
        log_.info("TerminalFunctionality::runCommand() invite user");
        InviteSender inviteSender(command, chatInfo);
        return inviteSender.doCommand();
    }

    else if (starts_with("w", command)) // TODO mwoznia problem z czekaniem na zaproszenie w mainie
    {
        // TODO mwoznia tak samo tutaj logi dodaj bo ja nie mam pojęcia co to jest
        ConsoleWindow::displayMainWindow();
        while (true)
        {

        }
    }

    else
    {
        log_.info("TerminalFunctionality::runCommand() command not found");
        return false;
    }

    return terminalCommand_->doCommand();
}

TerminalFunctionality::TerminalFunctionality(std::string chatFileWithPath, ChatStatus chatStatus)
            : chatFileWithPath_(chatFileWithPath)
            , chatStatus_(chatStatus)
{
    //NOOP
}



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
