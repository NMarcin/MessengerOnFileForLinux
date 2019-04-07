#include <ChatWindow.hpp>

WINDOW* ChatWindow::_displayMessageWindow = nullptr;
WINDOW* ChatWindow::_enterMessageWindow = nullptr;

void ChatWindow::displayChatWindows()
{
    clear();
    int sizeX, sizeY;
    getmaxyx(stdscr, sizeY, sizeX);
    _displayMessageWindow = newwin(sizeY * 0.75, sizeX, 1, 1);
    _enterMessageWindow = newwin(sizeY * 0.25 ,sizeX, sizeY * 0.8 + 1 ,1);
    wprintw(_enterMessageWindow, std::string(sizeX, '-').c_str());
    wrefresh(_displayMessageWindow);
    wrefresh(_enterMessageWindow);
    refresh();
}

void ChatWindow::deleteDisplayMesageWindow()
{
    delwin(_displayMessageWindow);
}

void ChatWindow::deleteEnterMesageWindow()
{
    delwin(_enterMessageWindow);
}

WINDOW* ChatWindow::getDisplayMessageWindow()
{
    return _displayMessageWindow;
}

WINDOW* ChatWindow::getEnterMessageWindow()
{
    return _enterMessageWindow;
}

void ChatWindow::displayEnterMessageWindow()
{
    int sizeX, sizeY;
    getmaxyx(stdscr, sizeY, sizeX);
    wclear(_enterMessageWindow);
    wprintw(_enterMessageWindow, std::string(sizeX, '-').c_str());
    mvwprintw(_enterMessageWindow, 2, 1, ">> ");
    wrefresh(_enterMessageWindow);
    nocbreak();
    echo();
}

void ChatWindow::displayDisplayMessageWindow(const std::string& message)
{
    wprintw(_displayMessageWindow, message.c_str());
    scrollok(_displayMessageWindow, true);
    idlok(_displayMessageWindow, true);
    wrefresh(_displayMessageWindow);
}
