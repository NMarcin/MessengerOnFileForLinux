#include <iostream>

#include <Display.hpp>

Display::Display(std::queue<std::string> messegeWaitingRoom)
        : messegeWaitingRoom_(std::make_unique<std::queue<std::string>>(messegeWaitingRoom))
{
    log.info("Display C-TOR");
}

Display::~Display()
{
    log.info("Display C-TOR");
}

bool Display::displayMessege() const
{
    std::cout << messegeWaitingRoom_->front() << std::endl;
    messegeWaitingRoom_->pop();
}
