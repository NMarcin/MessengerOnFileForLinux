#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <queue>
#include <ncurses.h>
#include <mutex>

#include <Sender.hpp>
#include <Receiver.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>
#include <Message.hpp>
#include <TerminalFunctionality.hpp>
#include "UserInactivityDetector.hpp"

class ConversationControl
{
public:
    void conversation();
    void conversationEpilog();
    ConversationControl(std::shared_ptr<ChatInformation> chatInfo);
    ~ConversationControl();
    static bool isConversationRunning_;

private:
    void getMessage();
    bool isMessagesToReadExist();
    void handleInterlocutorInactivity();
    void reciveMessage();
    void sendMessage();
    void stopThreads();
    void startThreads();
    void saveMessageToDisplay();

    std::unique_ptr<std::thread> getMessageToQueueThread_;
    std::unique_ptr<std::thread> sendMessageFromQueueThread_;
    std::unique_ptr<std::thread> reciveMessageThread_;
    std::unique_ptr<Receiver> receiver_;
    std::unique_ptr<Sender> sender_;
    std::shared_ptr<ChatInformation> chatInfo_;
    std::queue<Message> messageReadyToSend_;
    std::queue<PurgeMessage> messageToDisplay_;
    bool isThreadsRunning_;
    UserInactivityDetector userInactivityDetector_;
    bool userInactivityWasHandled;


    Logger log_{LogSpace::ChatStarter};
};
