#include "InformationPrinter.hpp"

#include <ncurses.h>
#include <chrono>
#include <thread>

void InformationPrinter::printInformation(const std::string& informationToPrint) const
{
    printw(informationToPrint.c_str());
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void InformationPrinter::printMainWindow() const
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

void InformationPrinter::printRegistrationWindow() const
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

void InformationPrinter::printSignInWindow() const
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
