#include <thread>
#include <chrono>

#include "ConsoleWindow.hpp"
#include "GlobalVariables.hpp"
#include "TerminalControl.hpp"

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
        constexpr int firstCharacterInAsciiCode = 0;
        constexpr int lastCharacterInAsciiCode = 127;
        constexpr int delCharacterInAsciiCode = 127;

        enteredCharacter = getch();

        if (firstCharacterInAsciiCode <= enteredCharacter and
            lastCharacterInAsciiCode >= enteredCharacter and
            '\n' != enteredCharacter)
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

void ConsoleWindow::deleteLastEnteredCharacter()
{
    constexpr int deleteCharacterLenght = 3;
    int cursorPositionX = 0;
    int cursorPositionY = 0;

    getyx(stdscr, cursorPositionY, cursorPositionX);
    cursorPositionX -= deleteCharacterLenght;
    mvprintw(cursorPositionY, cursorPositionX, std::string(deleteCharacterLenght, ' ').c_str());
    move(cursorPositionY, cursorPositionX);
}

void ConsoleWindow::updateTerminalSize()
{
    while(not TerminalControl::isInvitationExist)
    {
        getmaxyx(stdscr, ConsoleWindow::terminalSizeY, ConsoleWindow::terminalSizeX);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
