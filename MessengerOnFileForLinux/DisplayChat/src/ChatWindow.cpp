#include <ChatWindow.hpp>

WINDOW* ChatWindow::displayMessageWindow_ = nullptr;
WINDOW* ChatWindow::enterMessageWindow_ = nullptr;

//ChatWindow::getDisplayMessageWindow() = newwin(y * 0.75, x, 1, 1);//size y,x; wspolrzedne startu
//ChatWindow::getEnterMessageWindow() = newwin(y * 0.25 ,x, y * 0.8 + 1 ,1);

ChatWindow::ChatWindow()
{
    //NOOP
}

ChatWindow::~ChatWindow()
{
    //NOOP
}

void ChatWindow::newDisplayWindow(int x, int y)
{
    displayMessageWindow_ = newwin(y * 0.75, x, 1, 1);
}

void ChatWindow::newEnterWindow(int x, int y)
{
    enterMessageWindow_ = newwin(y * 0.25 ,x, y * 0.8 + 1 ,1);
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
