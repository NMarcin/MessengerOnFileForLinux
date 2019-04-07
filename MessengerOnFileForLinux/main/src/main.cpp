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
#include <Controler.hpp>

#define ever (;;)


void mnurzyns()
{
    std::cout << "mnurzyns:\n\n";
    fileLog("Witamy w logerze!", LogSpace::main);
}

void mwozniak()
{
    SignalHandling::createPosixSignalsHandling(SignalHandling::posixSignalHandlerInMainConsole);
    InformationPrinter informationPrinter;
    RegisterUser registerUser;
    registerUser.registerNewUser();
    clear();
    refresh();
    SignIn signIn(informationPrinter);
    signIn.signInUser();
    clear();
    refresh();

    Controler controler;
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
