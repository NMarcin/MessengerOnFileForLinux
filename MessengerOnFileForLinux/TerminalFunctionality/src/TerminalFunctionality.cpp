#include <TerminalFunctionality.hpp>

#include <HistoryDowloander.hpp>
#include <UserCommand.hpp>
#include <SignOut.hpp>
#include <ChatControl.hpp>
#include <Display.hpp>
#include <iostream>


bool starts_with(const std::string toFind, const std::string ourString);

bool TerminalFunctionality::runCommand(std::string command)
{
    if (starts_with(UserCommand::historyDowloander, command))
    {
        terminalCommand_ = std::make_unique<HistoryDowloander>(command);
        return terminalCommand_->doCommand();
    }
    else if (starts_with(UserCommand::endChat, command))
    {
        //TODO konczenie rozmowy
    }
    else if (starts_with(UserCommand::logout, command))
    {
        SignOut signOut;
        return signOut.signOutUser();
    }
    else if (starts_with(UserCommand::inviteUser, command))
    {
        std::string username = {command.begin()+7, command.end()};
        ChatControl control;
        //TODO mwoznia podpiac tu std::sginal
        //std::signal(SIGINT, sigintHandlerInChatConsole);
        control.conversationProlog(username, ChatRole::inviter);
    }
    else if (starts_with(UserCommand::help, command))
    {
        Display::displayMainWindow();
        printw("\n");
        printw("  PRZYKLADOWE KOMENDY ");
        refresh();
        //sleep(2);
    }
    else if (starts_with("w", command))
    {
        Display::displayMainWindow();
        while (true)
        {

        }
    }
    else
    {
        return false;   // TODO: kto obsluguje tego, ze nie ma takiej komendy?
    }
}

TerminalFunctionality::TerminalFunctionality()
{
    terminalCommand_ = nullptr;
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
