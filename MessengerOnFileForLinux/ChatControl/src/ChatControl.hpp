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
    void conversationProlog(const std::string& username, ChatRole chatRole);
    void conversationEpilog();

private:
    void conversation();
    void getMessage();
    void reciveMessage();
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const std::string& username);
    void sendMessage();
    void stopThreads();

    std::unique_ptr<std::thread> getMessageToQueueThread_;
    std::unique_ptr<std::thread> sendMessageFromQueueThread_;
    std::unique_ptr<std::thread> reciveMessageThread_;
    std::queue<std::unique_ptr<std::string>> messageWaitingRoom_;
    std::string chatFileWithPath_;
    MessageFlag messageFlag_;
    bool isThreadsRunning_;

    Logger log{LogSpace::ChatFile};

};
