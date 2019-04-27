#include <thread>
#include <ncurses.h>
#include <iostream>

#include "RegisterUser.hpp"
#include "SignIn.hpp"
#include "ConsoleWindow.hpp"
#include "TerminalFunctionality.hpp"
#include "Logger.hpp"
#include "ClasslessLogger.hpp"
#include "LogSpace.hpp"
#include "SignalHandling.hpp"
#include "Controler.hpp"

#define ever (;;)


void mnurzyns()
{
    std::cout << "mnurzyns:\n\n";
    fileLog("Witamy w logerze!", LogSpace::main);
}

void mwozniak()
{
    NcursesPrintToMainWindowOperationWrapper informationPrinter;
    SignalHandler signalHandler(informationPrinter);
    signalHandler.createPosixSignalsHandling(signalHandler.posixSignalHandlerInMainConsole);
    RegisterUser registerUser(informationPrinter, signalHandler);
    registerUser.registerNewUser();
    clear();
    refresh();
    SignIn signIn(informationPrinter, signalHandler);
    signIn.signInUser();
    clear();
    refresh();

    Controler controler(signalHandler);
    controler.controlUserAction();
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
