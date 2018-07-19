#include <SignalHandling.hpp>
#include <SignOut.hpp>
#include <ChatControl.hpp>

namespace SignalHandling
{

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
    chatControl.conversationEpilog();
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
}

}
