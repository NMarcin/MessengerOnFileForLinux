#pragma once

#include <ncurses.h>

class ChatWindow
{
public:
    ChatWindow();
    ~ChatWindow();

    //setWidnowssize x2;

    static WINDOW* getDisplayMessageWindow();
    static WINDOW* getEnterMessageWindow();

    static WINDOW* displayMessageWindow_;
    static WINDOW* enterMessageWindow_;

};
