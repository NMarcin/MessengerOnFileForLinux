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
