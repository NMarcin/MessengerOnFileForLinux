#include <ChatWindow.hpp>

WINDOW* ChatWindow::displayMessageWindow_ = nullptr;
WINDOW* ChatWindow::enterMessageWindow_ = nullptr;

ChatWindow::ChatWindow()
{
    //NOOP
}

ChatWindow::~ChatWindow()
{
    //NOOP
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
    int x, y;
    std::string frame;

    getmaxyx(stdscr, y, x);

    for (int i = 0; i < x; i++)
    {
        frame += "-";
    }

    wclear(enterMessageWindow_);
    wprintw(enterMessageWindow_, frame.c_str());
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
