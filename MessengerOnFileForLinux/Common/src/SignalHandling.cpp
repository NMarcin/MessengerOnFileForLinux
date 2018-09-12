#include <SignalHandling.hpp>
#include <SignOut.hpp>
#include <ConversationControl.hpp>

namespace SignalHandling
{

namespace
{
volatile std::sig_atomic_t signalStatus;
}

void sigintHandlerInMainConsole(int signal)
{
    fileLog("SIGINT handled in main console", LogSpace::Common);
    signalStatus = signal;
    SignOut signOut;
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
}

void sigintHandlerInChatConsole(int signal)
{
    fileLog("SIGINT handled in chat console", LogSpace::Common);
    signalStatus = signal;
    SignOut signOut;
    //ConversationControl conversationControl; //TODO !!! trzeba tu przekazac w jakis sposob chatFilePath i messageFlag
    //conversationControl.conversationEpilog();//TODO bo konsturktor musi przyjac te wartosc i zeby to dzialo
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
        //Jak poinformowac druga osobe ze kniec ? wyslac jej //unexpected_end ?
    //czy nie trzeba conversationEpilogWithError() ?
}

}
