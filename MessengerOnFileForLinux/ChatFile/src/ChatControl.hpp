#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <queue>

#include <Sender.hpp>
#include <Reciver.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

enum class MessageFlag
{
    readMessage,
    inviterMessage,
    recipientMessage
};

enum class ChatRole
{
    inviter,
    recipient
};


class ChatControl
{
public:
    ChatControl();
    ~ChatControl();
    void startConversation(const std::string& username, ChatRole chatRole);
    void endConversation();

private:
    void conversationControl();
    void getMessage();
    void reciveMessage();
    void sendMessage();
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const int pid);
    void stopThreads();

    std::unique_ptr<std::thread> getMessageThread_;
    std::unique_ptr<std::thread> sendMessageThread_;
    std::unique_ptr<std::thread> reciverThread_;
    std::queue<std::unique_ptr<std::string>> messageWaitingRoom_;
    std::string chatFileWithPath_;
    MessageFlag messageFlag_;
    bool isThreadsRunning_;

    Logger log{LogSpace::ChatFile};

};
