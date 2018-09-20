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

bool TerminalFunctionality::runCommand(std::string command,  TerminalControl* przekazujemyToZebyMiecDostepDoStartuRozmowyPrzyInvicie)
{
    if (starts_with(UserCommand::historyDowloander, command))
    {
        terminalCommand_ = std::make_unique<HistoryDowloander>(command, chatFileWithPath_);
    }
    else if (starts_with(UserCommand::endChat, command))
    {
         terminalCommand_ = std::make_unique<EndConversation>(command);
    }
    else if (starts_with(UserCommand::logout, command))
    {
        terminalCommand_ = std::make_unique<LoggingOut>(command);
    }
    else if (starts_with(UserCommand::inviteUser, command))
    {

        terminalCommand_ = std::make_unique<InviteSender>(command);
    }

    else if (starts_with("w", command)) // TODO mwoznia problem z czekaniem na zaproszenie w mainie
    {
        ConsoleWindow::displayMainWindow();
        while (true)
        {

        }
    }

    else
    {
        return false;   // TODO: kto obsluguje tego, ze nie ma takiej komendy?
    }

    return terminalCommand_->doCommand();
}

TerminalFunctionality::TerminalFunctionality(std::string chatFileWithPath)
            : chatFileWithPath_(chatFileWithPath)
{
    //NOOP
}

TerminalFunctionality::~TerminalFunctionality()
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
