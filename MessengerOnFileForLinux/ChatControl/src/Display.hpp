#pragma once
#include <queue>
#include <memory>
#include <ncurses.h>
#include <atomic>

#include <Logger.hpp>
#include <LogSpace.hpp>

namespace Display
{
    static std::atomic<int> terminalSizeX;
    static std::atomic<int> terminalSizeY;

    void displayMainWindow();
    void displayEnterMessageWindow(WINDOW* enterMessageWindow);
    void displayDisplayMessageWindow(WINDOW* displayMessageWindow, const std::string& message);
    void displayRegistrationMainWindow();
    void displayLoggedMainWindow();
    void updateTerminalSize();
    void initChatWindow(WINDOW* displayMessageWindow, WINDOW* enterMessageWindow);
    std::string getStringFromMainWindow();
}
