#pragma once
#include <memory>

#include <Sender.hpp>
#include <Reciver.hpp>

enum class ChatRole
{
    inviting,
    respondent
};

class ChatControl
{
public:
    ChatControl(const std::string& username);
    ~ChatControl();

    bool sendMessage() const;
    bool reciveMessage() const;

private:
    std::unique_ptr<std::string> findChatFolder(const std::string& username);
    std::unique_ptr<std::string> findChatFile(const std::string& folderName);

    std::unique_ptr<Sender> sender_;
    std::unique_ptr<Reciver> reciver_;
    std::string pathToChatFile_;
    ChatRole chatRole_;

};
