#include <iostream>
#include <math.h>
#include <string>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <csignal>
#include <stdlib.h>

#include <GlobalVariables.hpp>
#include <FileHandling.hpp>
#include <RegisterUser.hpp>
#include <SignIn.hpp>
#include <SignOut.hpp>
#include <LocalUser.hpp>
#include <ChatRequest.hpp>
#include <Sender.hpp>
#include <ChatControl.hpp>
#include <Display.hpp>
#include <TerminalFunctionality.hpp>

#include <Logger.hpp>
#include <ClasslessLogger.hpp>
#include <LogSpace.hpp>

namespace
{
volatile std::sig_atomic_t gSignalStatus;
}

void sigintHandlerInMainConsole(int signal)
{
    fileLog("SIGINT signal handled", LogSpace::main);
    gSignalStatus = signal;
    SignOut signOut;
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
}

void sigintHandlerInChatConsole(int signal)
{
    fileLog("SIGINT signal handled in chat console", LogSpace::main);
    gSignalStatus = signal;
    SignOut signOut;
    ChatControl chatControl;
    signOut.signOutUser();
    chatControl.conversationEpilog();
    exit (EXIT_SUCCESS);
}
void (*pf)(ChatControl&);
void mnurzyns()
{
    std::cout << "mnurzyns:\n\n";
    fileLog("Witamy w logerze!", LogSpace::main);
}

void mwozniak()
{
    std::signal(SIGINT, sigintHandlerInMainConsole);
    std::thread waitForInvitation(lookForInvitation);

    RegisterUser registerUser;
    SignIn signIn;
    TerminalFunctionality terminal;

    for(;;)
    {
        registerUser.registerNewUser();
        clear();
        refresh();
        signIn.signInUser();
        clear();
        refresh();
        Display::displayMainWindow();
        char command[512];
        getstr(command);

        terminal.runCommand(command);

        //TODO mawoznia tutaj powinno byc wywolwyawnie runCommand() dla kazdego stringa wejscioweg
        /*
        if ( strcmp("invite marcin", command) == 0)
        {
            ChatControl control;
            std::signal(SIGINT, sigintHandlerInChatConsole);
            control.conversationProlog("marcin", ChatRole::inviter);
        }
        else if ( strcmp("invite tomek", command) == 0)
        {
            //std::signal(SIGINT, sigintHandlerInChatConsole);

            ChatControl control;
            control.conversationProlog("tomek", ChatRole::inviter);
        }
        else if ( strcmp("logout", command) == 0)
        {
            //std::signal(SIGINT, sigintHandlerInChatConsole);

            terminal.runCommand(command);
        }

        else if ( strcmp("w", command) == 0) //TODO mawaoznia ogarnac co z tym waitem
        {
            Display::displayMainWindow();
            while (true)
            {

            }
        }
        */
    }
}

enum class Run
{
    mnurzyns,
    mwozniak,
    both
};

int main(int argc, char **argv)
{
    //Run version = Run::mnurzyns;
    Run version = Run::mwozniak;

    if (Run::mnurzyns == version)
    {
        mnurzyns();
    }
    else if (Run::mwozniak == version)
    {
        mwozniak();
    }
    else if (Run::both == version)
    {
        mnurzyns();
        std::cout << std::endl << std::endl << std::endl;
        mwozniak();
    }
    return 0;
}
