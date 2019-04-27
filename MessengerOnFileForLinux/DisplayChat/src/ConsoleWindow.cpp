#include <thread>
#include <chrono>

#include "ConsoleWindow.hpp"
#include "GlobalVariables.hpp"
#include "TerminalControl.hpp"

namespace
{
constexpr int firstAsciiCharacter = 0;
constexpr int lastAsciiCharacter = 127;
}//namespace

std::string ConsoleWindow::getStringFromConsoleWindow()
{
    std::string output;
    char enteredCharacter {};
    while ('\n' != enteredCharacter)
    {
        constexpr int delCharacterInAsciiCode = 127;

        enteredCharacter = getch();

        if (isCharacterInCorrectRange(enteredCharacter))
        {
            if (delCharacterInAsciiCode == enteredCharacter)
            {
                deleteLastEnteredCharacter();
            }
            else
            {
                output += enteredCharacter;
            }
        }
    }
    return output;
}

bool ConsoleWindow::isCharacterInCorrectRange(const char character)
{
    return firstAsciiCharacter <= character and
           lastAsciiCharacter >= character and
           '\n' != character;
}

void ConsoleWindow::deleteLastEnteredCharacter()
{
    constexpr int delCharacterLenght = 3;
    int cursorPositionX = 0;
    int cursorPositionY = 0;

    getyx(stdscr, cursorPositionY, cursorPositionX);
    cursorPositionX -= delCharacterLenght;
    mvprintw(cursorPositionY, cursorPositionX, std::string(delCharacterLenght, ' ').c_str());
    move(cursorPositionY, cursorPositionX);
}
