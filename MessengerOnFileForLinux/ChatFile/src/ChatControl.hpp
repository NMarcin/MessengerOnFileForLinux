#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <iostream>
#include <Sender.hpp>
#include <Reciver.hpp>
#include <User.hpp>

enum class MessageFlag
{
    inviter = 1,
    recipient = 2
};

class ChatControl
{
public:
    ChatControl();
    ~ChatControl();

    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const int pid);
    void endConversation();

private:
    void conversationControl();
    std::unique_ptr<std::string> getChatFolderName(const std::string& username);
    std::unique_ptr<std::string> getChatFileName(const std::string& folderName);
    void setPathToChatFile(const std::string& username);

    std::vector<std::thread> communicationThreads_;
    std::string pathToChatFile_;
    MessageFlag messageFlag_;
    bool isChatRunning_ = true;

};
