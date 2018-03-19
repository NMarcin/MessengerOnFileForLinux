#pragma once
#include <memory>
#include <string>

class Sender
{
public:
    Sender();
    ~Sender();

    bool sendMessage(const std::string& pathToChatFile, int flag) const;

private:
    std::unique_ptr<std::string> enterMessage() const;
    std::unique_ptr<std::string> prepearMessageToSend(const std::string& rowMessage, int flag) const;
    bool setNewMessageFlag(const std::string& folderName) const;
};
