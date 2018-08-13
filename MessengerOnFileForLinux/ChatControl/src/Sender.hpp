#pragma once
#include <memory>
#include <string>
#include <ncurses.h>

#include <Logger.hpp>
#include <LogSpace.hpp>

class Sender
{
public:
    Sender(const std::string& pathToChatFile, int chatFlag, WINDOW* subwin);
    ~Sender();

    std::string getMessageToSend() const;
    bool sendMessage(const std::string& message) const;

private:
    std::string getMessageFromStdin() const;
    std::string getActualDateTime() const;
    std::string prepareMessageToSend(const std::string& rowMessage) const;
    bool isTerminalCommand(const std::string& message) const;
    bool setNewMessageFlag() const;

    std::string chatFilenameWithPath_;
    int chatFlag_;

    WINDOW* enterMessageWindow_;
    Logger log {LogSpace::ChatFile};
};
