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
    log_.function("TerminalFunctionality::runCommand()");
    if (starts_with(UserCommand::historyDowloander, command) && ChatStatus::conversation == chatStatus_)
    {
        log_.info("TerminalFunctionality::runCommand() historyDowloander command");
        terminalCommand_ = std::make_unique<HistoryDowloander>(command, chatFileWithPath_);
    }
    else if (starts_with(UserCommand::endChat, command) && ChatStatus::conversation == chatStatus_)
    {
        log_.info("TerminalFunctionality::runCommand() endChat command");
        //TODO mwozniak konczenie rozmowy (END)
    }
    else if (starts_with(UserCommand::logout, command))
    {
        log_.info("TerminalFunctionality::runCommand() logout command");
        terminalCommand_ = std::make_unique<LoggingOut>(command);
    }
    else if (starts_with(UserCommand::inviteUser, command) && ChatStatus::terminal == chatStatus_) // TODO mwoznia zastosować schemat polimorfizmu, dodatkowo architektura tego jest zła, ponieważ ChatControl ma istnieć cały czas
    {
        log_.info("TerminalFunctionality::runCommand() inviteUser command");
        auto beginOfUsernameInCommand = command.begin()+7;  // TODO mwoznia 7 is a little bit magic number
        std::string username = {beginOfUsernameInCommand, command.end()};
        TerminalControl terminalControl(ChatStatus::terminal);  // TODO mwozniak to nie powinno tutaj tworzyć nowego TerminalControl
        terminalControl.startConversation(username, ChatRole::inviter);
    }
    else if (starts_with(UserCommand::help, command))       // TODO mwoznia co to jest? to i ponizsze?
    {
        log_.info("TerminalFunctionality::runCommand() help command");
        ConsoleWindow::displayMainWindow();
        printw("\n");
        printw("  PRZYKLADOWE KOMENDY ");
        refresh();
        //sleep(2);
    }
    else if (starts_with("w", command)) // TODO mwoznia co to jest? Nie wiem co dodać: ChatStatus::terminal == chatStatus_
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
