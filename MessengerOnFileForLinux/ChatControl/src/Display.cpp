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

void Display::updateTerminalSize()
{
    while(isMessengerRunnig)
    {
        getmaxyx(stdscr, Display::terminalSizeY, Display::terminalSizeX);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}


