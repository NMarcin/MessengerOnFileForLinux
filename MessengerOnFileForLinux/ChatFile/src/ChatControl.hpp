#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <iostream>
#include <Sender.hpp>
#include <Reciver.hpp>
#include <User.hpp>

enum class ChatRole
{
    inviter = 1,
    respondent = 2
};

class ChatControl
{
public:
    ChatControl();
    ~ChatControl();

    void startConversationAsInviter(const std::string& username);
    void startConversationAsRespondent(const int pid);
    void endConversation();

private:
    void setChatPathWithFile(const std::string& username);
    void conversationControl();
    std::unique_ptr<std::string> getChatFolderName(const std::string& username);
    std::unique_ptr<std::string> getChatFileName(const std::string& folderName);

    std::thread senderThread;
    std::thread reciverThread;
    std::string pathToChatFile_;
    ChatRole chatRole_;
    bool isChatRunning = true;

};
