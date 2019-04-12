#pragma once

#include <ncurses.h>
#include <string>
#include "Logger.hpp"
#include "LogSpace.hpp"
#include "ClasslessLogger.hpp"

class ChatWindow
{
public:
    ChatWindow() = default;
    ~ChatWindow() = default;

    ChatWindow(ChatWindow &&) = delete;
    ChatWindow operator=(ChatWindow &&) = delete;
    ChatWindow(const ChatWindow &) = delete;
    ChatWindow operator=(const ChatWindow &) = delete;

    static void displayChatWindows();
    static void deleteDisplayMesageWindow();
    static void deleteEnterMesageWindow();
    static void displayEnterMessageWindow();
    static void displayDisplayMessageWindow(const std::string& message);
    static WINDOW* getDisplayMessageWindow();
    static WINDOW* getEnterMessageWindow();

    static WINDOW* _displayMessageWindow;
    static WINDOW* _enterMessageWindow;
};
