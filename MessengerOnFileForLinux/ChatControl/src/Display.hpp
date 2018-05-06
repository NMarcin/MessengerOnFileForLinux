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
    void displayRegistrationMainWindow();
    void displayLoggedMainWindow();
    void updateTerminalSize();
    std::string getStringFromMainWindow();
}


