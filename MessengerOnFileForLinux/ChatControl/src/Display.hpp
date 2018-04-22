#pragma once
#include <queue>
#include <memory>

#include <Logger.hpp>
#include <LogSpace.hpp>

class Display
{
public:
    Display(std::queue<std::string> messegeWaitingRoom);
    ~Display();
    bool displayMessege() const;

private:

    bool getMessegeFromQueue(std::queue<std::string>& messegeWaitingRoom) const;

    std::unique_ptr<std::queue<std::string>> messegeWaitingRoom_;

    Logger log {LogSpace::ChatControl};
};

