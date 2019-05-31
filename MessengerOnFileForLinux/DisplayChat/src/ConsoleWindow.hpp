#pragma once
#include <queue>
#include <memory>
#include <ncurses.h>
#include <atomic>

#include "Logger.hpp"
#include "LogSpace.hpp"

namespace ConsoleWindow
{
    void deleteLastEnteredCharacter();
    std::string getStringFromConsoleWindow();
    bool isCharacterInCorrectRange(const char character);
}
