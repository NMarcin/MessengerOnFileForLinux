#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <queue>
#include <ncurses.h>

#include <Sender.hpp>
#include <Receiver.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>
#include <Message.hpp>

class ConversationControl
{
public:
    void conversation();
    void conversationEpilog();
    ConversationControl(const std::string& chatFileWithPath, MessageFlag messageFlag);
    ~ConversationControl();

private:
    void getMessage();
    void reciveMessage();
    void sendMessage();
    void stopThreads();
    void startThreads();

    std::unique_ptr<std::thread> getMessageToQueueThread_;
    std::unique_ptr<std::thread> sendMessageFromQueueThread_;
    std::unique_ptr<std::thread> reciveMessageThread_;

    std::queue<std::string> messageReadyToSend_;
    std::queue<std::string> messageToDisplay_;

    std::string chatFileWithPath_;
    MessageFlag messageFlag_;
    bool isThreadsRunning_;

    Logger log{LogSpace::ChatFile};
};
