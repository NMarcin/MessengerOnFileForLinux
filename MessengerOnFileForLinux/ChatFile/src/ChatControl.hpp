#pragma once
#include <memory>

#include <Sender.hpp>
#include <Reciver.hpp>

enum class ChatRole
{
    inviting = 1,
    respondent = 2
};

class ChatControl
{
public:
    ChatControl(const std::string& username);
    ~ChatControl();

    bool sendMessage() const;
    bool reciveMessage() const;

private:
    std::unique_ptr<std::string> getChatFolderName(const std::string& username);
    std::unique_ptr<std::string> getChatFileName(const std::string& folderName);

    std::unique_ptr<Sender> sender_;
    std::unique_ptr<Reciver> reciver_;
    std::string pathToChatFile_;
    ChatRole chatRole_;

};
