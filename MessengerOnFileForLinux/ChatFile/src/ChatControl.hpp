#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <iostream>
#include <queue>

#include <Sender.hpp>
#include <Reciver.hpp>
#include <User.hpp>

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
    //TODO zmienic chatFile i ChatRequest zeby zwracaly sciezke do pliku rozmowy.
    //Bedzie sie to odbywalo w startAsInviter/Reciptnet
    void startConversation(const std::string& username, ChatRole chatRole);
    void endConversation();

private:
    void conversationControl();
    void startConversationAsInviter(const std::string& username);
    void startConversationAsRecipient(const int pid);
    void stopThreads();

    std::unique_ptr<std::thread> getMessageThread_;
    std::unique_ptr<std::thread> sendMessageThread_;
    std::unique_ptr<std::thread> reciverThread_;
    std::queue<std::unique_ptr<std::string>> messageWaitingRoom_;
    std::string chatFilenameWithPath_;
    MessageFlag messageFlag_;
    bool isThreadsRunning_;

};
