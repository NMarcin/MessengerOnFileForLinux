#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <queue>
#include <ncurses.h>

#include <Sender.hpp>
#include <Receiver.hpp>
#include <ChatData.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class ConversationControl //: public ChatControl
{
public:
    void conversation();
    void conversationEpilog();
    ~ConversationControl();

private:
    void getMessage();
    void reciveMessage();
    void sendMessage();
    void stopThreads();

    std::unique_ptr<std::thread> getMessageToQueueThread_;
    std::unique_ptr<std::thread> sendMessageFromQueueThread_;
    std::unique_ptr<std::thread> reciveMessageThread_;

    std::queue<std::string> messageReadyToSend_;
    std::queue<std::string> messageToDisplay_;

    std::string chatFileWithPath_;
    MessageFlag messageFlag_;
    bool isThreadsRunning_;

    WINDOW* displayMessageWindow_;                                              // TODO mwozniak to powinno być jako klasa, która udostępniainterfejs, a nie część ChatControlu
    WINDOW* enterMessageWindow_;

    Logger log{LogSpace::ChatFile};
};
