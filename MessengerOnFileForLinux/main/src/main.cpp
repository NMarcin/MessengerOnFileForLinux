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
#include <csignal>
#define ever (;;)


void mnurzyns()
{

}

void mwozniak()
{
    initscr(); //to musi byc

    RegisterUser registerUser;
    SignIn signIn;

    std::signal(SIGINT, SignalHandling::sigintHandlerInMainConsole);
    registerUser.registerNewUser();
    clear();
    refresh();

    signIn.signInUser();
    clear();
    refresh();//mawoznia ncourses dziala do momentu glownej petli, potem roznie. Ogolnie prawie
    //jest mainWindow. Trzeba jeszcze ChatWindow

    endwin();

    //std::signal(SIGWINCH, SignalHandling::NCoursesSignal::resizeHandlerInMainWindow);
    //ConsoleWindow::displayMainWindow();

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
