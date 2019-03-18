#include <ChatWindow.hpp>

WINDOW* ChatWindow::displayMessageWindow_ = nullptr;
WINDOW* ChatWindow::enterMessageWindow_ = nullptr;

void ChatWindow::displayChatWindows()
{
    clear();
    int sizeX, sizeY;
    getmaxyx(stdscr, sizeY, sizeX);
    displayMessageWindow_ = newwin(sizeY * 0.75, sizeX, 1, 1);
    enterMessageWindow_ = newwin(sizeY * 0.25 ,sizeX, sizeY * 0.8 + 1 ,1);
    wprintw(enterMessageWindow_, std::string(sizeX, '-').c_str());
    wrefresh(displayMessageWindow_);
    wrefresh(enterMessageWindow_);
    refresh();
}

void ChatWindow::deleteDisplayMesageWindow()
{
    delwin(displayMessageWindow_);
}

void ChatWindow::deleteEnterMesageWindow()
{
    delwin(enterMessageWindow_);
}

WINDOW* ChatWindow::getDisplayMessageWindow()
{
    return displayMessageWindow_;
}

WINDOW* ChatWindow::getEnterMessageWindow()
{
    return enterMessageWindow_;
}

void ChatWindow::displayEnterMessageWindow()
{
    int sizeX, sizeY;
    getmaxyx(stdscr, sizeY, sizeX);
    wclear(enterMessageWindow_);
    wprintw(enterMessageWindow_, std::string(sizeX, '-').c_str());
    mvwprintw(enterMessageWindow_, 2, 1, ">> ");
    wrefresh(enterMessageWindow_);
    nocbreak();
    echo();
}

void ChatWindow::displayDisplayMessageWindow(const std::string& message)
{
    wprintw(displayMessageWindow_, message.c_str());
    scrollok(displayMessageWindow_, true);
    idlok(displayMessageWindow_, true);
    wrefresh(displayMessageWindow_);
}
