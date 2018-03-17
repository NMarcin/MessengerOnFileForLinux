#pragma once
#include <memory>
#include <string>

class Sender
{
public:
    Sender();
    ~Sender();

    bool sendMessage(const std::string& username) const;

private:
    std::unique_ptr<std::string> findChatFolder(const std::string& username) const;
    std::unique_ptr<std::string> findChatFile(const std::string& folderName) const;
    std::unique_ptr<std::string> enterMessage() const;
    std::unique_ptr<std::string> prepearMessageToSend(const std::string& message) const;
};
