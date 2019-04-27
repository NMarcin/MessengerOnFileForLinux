#pragma once
#include <queue>
#include <memory>
#include <ncurses.h>
#include <atomic>

#include "Logger.hpp"
#include "LogSpace.hpp"

namespace ConsoleWindow
{
    static std::atomic<int> terminalSizeX;
    static std::atomic<int> terminalSizeY;

    void displayMainWindow();
    void displayRegistrationWindow();
    void displaySignInWindow();
    void deleteLastEnteredCharacter();
    std::string getStringFromConsoleWindow();
    bool isCharacterInCorrectRange(const char character);
}
