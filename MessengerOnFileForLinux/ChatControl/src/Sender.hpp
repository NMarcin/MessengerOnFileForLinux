#pragma once
#include <memory>
#include <string>
#include <ncurses.h>

#include <Message.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class Sender
{
public:
    Sender(const std::string& pathToChatFile, MessageFlag messageFlag);
    ~Sender();

    Message getMessageToSend() const;
    bool sendMessage(const Message& message) const;

private:
    std::string getMessageFromStdin() const;
    Message prepareMessageToSend(const std::string& rowMessage) const;
    bool isTerminalCommand(const std::string& message) const;
    bool setNewMessageFlag() const;

    std::string chatFilenameWithPath_;
    MessageFlag messageFlag_;

    Logger log {LogSpace::ChatFile};
};
