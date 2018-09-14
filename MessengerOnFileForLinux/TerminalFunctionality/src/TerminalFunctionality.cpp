#include <TerminalFunctionality.hpp>


#include <UserCommand.hpp>

#include <HistoryDowloander.hpp>
#include <LoggingOut.hpp>
#include <GlobalVariables.hpp>
#include <TerminalControl.hpp>
#include <ConsoleWindow.hpp>
#include <iostream>


bool starts_with(const std::string toFind, const std::string ourString);

bool TerminalFunctionality::runCommand(std::string command)
{
    if (starts_with(UserCommand::historyDowloander, command))
    {
        terminalCommand_ = std::make_unique<HistoryDowloander>(command, chatFileWithPath_);
    }
    else if (starts_with(UserCommand::endChat, command))
    {
        //TODO konczenie rozmowy
    }
    else if (starts_with(UserCommand::logout, command))
    {
        terminalCommand_ = std::make_unique<LoggingOut>(command);
    }
    else if (starts_with(UserCommand::inviteUser, command)) // TODO mwoznia zastosować schemat polimorfizmu, dodatkowo architektura tego jest zła, ponieważ ChatControl ma istnieć cały czas
    {
        auto beginOfUsernameInCommand = command.begin()+7;  // TODO mwoznia 7 is a little bit magic number
        std::string username = {beginOfUsernameInCommand, command.end()};
        TerminalControl terminalControl;
        terminalControl.startConversation(username, MessageFlag::inviterMessage);    // TODO mnurzyns check it later!!!!
    }
    else if (starts_with(UserCommand::help, command))       // TODO mwoznia co to jest? to i ponizsze?
    {
        ConsoleWindow::displayMainWindow();
        printw("\n");
        printw("  PRZYKLADOWE KOMENDY ");
        refresh();
        //sleep(2);
    }
    else if (starts_with("w", command))
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
