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
