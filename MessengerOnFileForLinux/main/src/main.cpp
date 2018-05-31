#include <iostream>
#include <math.h>
#include <string>
#include <thread>
#include <chrono>
#include <ncurses.h>

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

#include <Logger.hpp>
#include <ClasslessLogger.hpp>
#include <LogSpace.hpp>

void ncourses();
void mainWindow();


void mnurzyns()
{
    std::cout << "mnurzyns:\n\n";
    fileLog("Witamy w logerze!", LogSpace::main);
}

void mwozniak()
{
  //FileInterface::Modification::updateRowField("/home/mawoznia/marcin/MessengerOnFileForLinux/MessengerOnFileForLinux/build/bin/test.txt"
         //                              , "'[1]'", "0",);

    initscr();

    std::thread waitForInvitation(lookForInvitation);
    std::thread getTerminalSize(Display::updateTerminalSize);

    RegisterUser registerUser;
    SignIn signIn;
    registerUser.registerNewUser();
    clear();
    refresh();
    signIn.signInUser();
    clear();
    refresh();

    for(;;)
    {
        Display::displayMainWindow();
        char command[512];
        getstr(command);

        if ( strcmp("invite marcin", command) == 0)
        {
            ChatControl control;
            control.conversationProlog("marcin", ChatRole::inviter);
        }
        else if ( strcmp("invite tomek", command) == 0)
        {
            ChatControl control;
            control.conversationProlog("tomek", ChatRole::inviter);
        }

         else if ( strcmp("wait", command) == 0)
        {
            while (true)
            {
                refresh();
            }
        }
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

std::string getstring(WINDOW* subwindow)
{
    std::string input;
    nocbreak();
    echo();
    int ch = wgetch(subwindow);
    while ( ch != '\n' )
    {

        input.push_back( ch );
        ch = wgetch(subwindow);
    }
    return input;
}

void showFrame()
{
    /*
    for (int i = 0; i < x/3; i++)
    {
        printw("X  ");
    }
    printw("\n");

    for (int i = 0; i < y; i++)
    {
        printw("X");
        for (int j = 0; j < x - 2; j++)
        {
            printw(" ");
        }
        printw("X\n");
    }

    move(y-1,0);
    for (int i = 0; i < x/3; i++)
    {
        printw("X  ");
    }
    */

    printw("##################### MESSENGER ##################### \n");
    for (int i = 0; i < 10;  i++)
    {
        printw("#                                                                                                                                   # \n");
    }
    printw("##################################################### \n");
}

void mainWindow()
{
    initscr();

    showFrame();
    move(2,2);
    std::string user = getenv("USER");
    std::thread waitForInvitation(lookForInvitation);
    printw(("   .......::::::Welcome " + user + ":::::::.......").c_str());

    int option = 0;
    SignOut signOut;
    signOut.signOutUser();
    bool isSignInSuccesfully = false;
    while (!isSignInSuccesfully)
    {
        mvprintw(4,2,"Choose option: ");
        mvprintw(5,2,"(1) Register");
        mvprintw(6,2,"(2) SignIn");
        move(4, 17);

        option = getch();
        clear();


        if ('1' == option)
        {
            showFrame();
            move(2, 2);
            refresh();
            RegisterUser registerUser;
            SignIn signIn;
            registerUser.registerNewUser();
            move(2, 2);
            clear();
            showFrame();
            mvprintw(2,2,("   .......::::::Welcome " + user + ":::::::.......").c_str());
            mvprintw(4,2,"___Sign In___ ");
            refresh();

            if (signIn.signInUser())
            {
                isSignInSuccesfully = true;
            }
        }

        else if ('2'== option)
        {
            showFrame();
            move(2, 2);
            refresh();

            SignIn signIn;
            if (signIn.signInUser())
            {
                isSignInSuccesfully = true;
            }
        }
    }

    while (true)
    {
        clear();
        showFrame();
        refresh();
        mvprintw(2,2,"Choose option: ");
        mvprintw(3,2,"(1) Invite user");
        mvprintw(4,2,"(2) Wait for invitation");
        mvprintw(5,2,">> ");

        option = getch();

        if ('1' == option)
        {


            clear();
            refresh();
            showFrame();
            mvprintw(2,2,("   .......::::::Welcome " + user + ":::::::.......").c_str());
            mvprintw(3,2," who do you want to invite? Invite ");
            move(4,2);
            refresh();
            std::string who;
            std::cin >> who;

            ChatControl control;
            control.conversationProlog(who, ChatRole::inviter);
        }

        else
        {
            clear();
            showFrame();
            move(2,2);
            refresh();

            while (true)
            {}
        }
    }

    waitForInvitation.join();
    signOut.signOutUser();

    getch();
    endwin();

}

void ncourses()
{
    initscr();
    printw("##################### MESSENGER ##################### \n");

    WINDOW* subwindow = newwin(15,40,1,1);//size y,x; wspolrzedne startu
    WINDOW* subwindow2 = newwin(3,40,15,1);

    refresh();

    box(subwindow,0,0); //obrabia w liniue
    box(subwindow2,0,0);

    refresh();
    wrefresh(subwindow);
    refresh();
    wrefresh(subwindow2);

    int i = 1;
    for (;;)
    {
        std::string time = static_cast<std::string>(__TIME__) + " : ";
        wmove(subwindow2, 1, 1);
        mvwprintw(subwindow2, 1, 1, time.c_str());
        wrefresh(subwindow2);
        std::string text = getstring(subwindow2);
        mvwprintw(subwindow, i, 1, text.c_str());

        refresh();
        wclear(subwindow2);
        box(subwindow2,0,0);
        wrefresh(subwindow);

        i++;
        refresh();
        wrefresh(subwindow2);
    }

    getch();
    delwin(subwindow);
    delwin(subwindow2);
    endwin();

}
