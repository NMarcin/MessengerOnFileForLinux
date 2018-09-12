#include <thread>
#include <ncurses.h>

#include <RegisterUser.hpp>
#include <SignIn.hpp>
#include <ConsoleWindow.hpp>
#include <TerminalFunctionality.hpp>
#include <GlobalVariables.hpp> //lookforInivitation() init function
#include <Logger.hpp>
#include <ClasslessLogger.hpp>
#include <LogSpace.hpp>
#include <SignalHandling.hpp>

#define ever (;;)


void mnurzyns()
{
    std::cout << "mnurzyns:\n\n";
    fileLog("Witamy w logerze!", LogSpace::main);
}

void mwozniak()
{

    std::signal(SIGINT, SignalHandling::sigintHandlerInMainConsole);
    std::thread waitForInvitation(lookForInvitation);

    RegisterUser registerUser;
    SignIn signIn;
    TerminalFunctionality terminal;

    for ever
    {
        registerUser.registerNewUser();
        clear();
        refresh();
        signIn.signInUser();
        clear();
        refresh();
        ConsoleWindow::displayMainWindow();
        char command[512];
        getstr(command);
        terminal.runCommand(command);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
