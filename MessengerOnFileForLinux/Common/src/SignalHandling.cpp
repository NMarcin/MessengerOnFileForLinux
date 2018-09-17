#include <SignalHandling.hpp>
#include <SignOut.hpp>
#include <ConversationControl.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

#include <utility>
#include <cstring>

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
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
}

}
