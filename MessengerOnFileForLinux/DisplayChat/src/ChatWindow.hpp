#pragma once

#include <ncurses.h>
#include <string>

class ChatWindow
{
public:
    ChatWindow();
    ~ChatWindow();

    //setWidnowssize x2;

    static WINDOW* getDisplayMessageWindow();
    static WINDOW* getEnterMessageWindow();
    static void displayEnterMessageWindow();
    static void displayDisplayMessageWindow(const std::string& message);

    static WINDOW* displayMessageWindow_;
    static WINDOW* enterMessageWindow_;

};
