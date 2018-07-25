#pragma once
#include <memory>
#include <string>
#include <ncurses.h>

#include <FileHandling.hpp>     // TODO mwozniak to nie powinno byc tutaj, a w .cpp, nie korzystasz z tego w tym pliku
#include <Logger.hpp>
#include <LogSpace.hpp>

class Sender
{
public:
    Sender(const std::string& pathToChatFile, int chatFlag, WINDOW* subwin);
    ~Sender();

    std::unique_ptr<std::string> getMessageToSend() const;
    bool sendMessage(const std::string& message) const;

private:
    std::unique_ptr<std::string> getMessageFromStdin() const;
    std::unique_ptr<std::string> getActualDateTime() const;
    std::unique_ptr<std::string> prepareMessageToSend(const std::string& rowMessage) const;
    bool isTerminalCommand(const std::string& message) const;
    bool setNewMessageFlag() const;

    std::string chatFilenameWithPath_;
    int chatFlag_;

    WINDOW* enterMessageWindow_;
    Logger log {LogSpace::ChatFile};
};
