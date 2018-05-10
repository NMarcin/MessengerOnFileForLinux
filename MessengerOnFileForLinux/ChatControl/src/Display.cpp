#include <iostream>

#include <Display.hpp>
#include <GlobalVariables.hpp>
#include <thread>
#include <chrono>


void Display::displayMainWindow()
{
    clear();
    move(0,0);
    printw("You are currently logged as ");
    printw(getenv("USER"));
    move(2,0);
    printw(">>");
    move(2,3);
    refresh();
}

void Display::displayRegistrationMainWindow()
{
    clear();
    move(0,0);
    printw("Hello ");
    printw(getenv("USER"));
    printw(". You are using messenger first time. You need create account.");
    move(2,0);
    refresh();
}

void Display::displayLoggedMainWindow()
{
    clear();
    move(0,0);
    printw("Hello ");
    printw(getenv("USER"));
    printw(". If you want use messenger, you need to log in.");
    move(2,0);
    refresh();
}

std::string Display::getStringFromMainWindow()
{
    std::string input;
    nocbreak();
    echo();
    int ch = getch();
    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }
    return input;
}

void Display::displayEnterMessageWindow(WINDOW* enterMessageWindow)
{
    int x, y;
    std::string frame;

    getmaxyx(stdscr, y, x);

    for (int i = 0; i < x; i++)
    {
        frame += "-";
    }

    wclear(enterMessageWindow);
    wprintw(enterMessageWindow, frame.c_str());
    mvwprintw(enterMessageWindow, 2, 1, ">> ");
    wrefresh(enterMessageWindow);
    nocbreak();
    echo();
}

void Display::displayDisplayMessageWindow(WINDOW* displayMessageWindow, const std::string& message)
{
    wprintw(displayMessageWindow, message.c_str());
    scrollok(displayMessageWindow, true);
    idlok(displayMessageWindow, true);
    wrefresh(displayMessageWindow);
}

void Display::initChatWindow(WINDOW* displayMessageWindow, WINDOW* enterMessageWindow)
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    displayMessageWindow = newwin(y * 0.75, x, 1, 1);//size y,x; wspolrzedne startu
    enterMessageWindow = newwin(y * 0.25 ,x, y * 0.8 + 1 ,1);

    std::string frame;
    for (int i = 0; i < x; i++)
    {
        frame += "-";
    }

    wprintw(enterMessageWindow, frame.c_str());
    wrefresh(displayMessageWindow);
    wrefresh(enterMessageWindow);
    refresh();
}

void Display::updateTerminalSize()
{
    while(isMessengerRunnig)
    {
        getmaxyx(stdscr, Display::terminalSizeY, Display::terminalSizeX);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}


