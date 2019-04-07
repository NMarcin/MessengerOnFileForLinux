#pragma once
#include <memory>
#include <string>
#include <ncurses.h>

#include <Message.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>
#include <TerminalFunctionality.hpp>

class Sender
{
public:
    Sender(std::shared_ptr<ChatInformation> chatInfo);
    ~Sender() = default;

    Sender(Sender &&) = delete;
    Sender operator=(Sender &&) = delete;
    Sender(const Sender &) = delete;
    Sender operator=(const Sender &) = delete;

    std::unique_ptr<Message> getMessageToSend() const;
    bool sendMessage(const Message& message) const;

private:
    std::string getMessageFromStdin() const;
    std::unique_ptr<Message> prepareMessageToSend(const std::string& rowMessage) const;
    bool isTerminalCommand(const std::string& message) const;
    bool setNewMessageFlag() const;

    std::shared_ptr<ChatInformation> _chatInfo;
    Logger _log {LogSpace::ChatControl};
};
