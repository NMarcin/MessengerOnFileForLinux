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

void ConsoleWindow::displayMainWindow()
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

void ConsoleWindow::displayRegistrationWindow()
{
    clear();
    move(0,0);
    printw("Hello ");
    printw(getenv("USER"));
    printw(". You are using messenger first time. You need create account. Enter your password twice.");
    move(2,0);
    printw("Enter the password : ");
    refresh();
}

void ConsoleWindow::displaySignInWindow()
{
    clear();
    move(0,0);
    printw("Hello ");
    printw(getenv("USER"));
    printw(". If you want use messenger, you need to log in.");
    move(2,0);
    printw("Enter the password : ");
    refresh();
}

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
