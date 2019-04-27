#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <signal.h>
#include <queue>
#include <ncurses.h>

#include "Sender.hpp"
#include "Receiver.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"
#include "Message.hpp"
#include "TerminalFunctionality.hpp"
#include "UserInactivityDetector.hpp"
#include "SignalHandling.hpp"
#include "NcursesPrintOperationWrapper.hpp"

class ConversationControl
{
public:
    void conversation();
    void conversationEpilog();

    ConversationControl(std::shared_ptr<ChatInformation> chatInfo,
                        const SignalHandler& signalHandler,
                        const NcursesPrintOperationWrapper& informationPrinter);
    ~ConversationControl();

    ConversationControl(ConversationControl &&) = delete;
    ConversationControl operator=(ConversationControl &&) = delete;
    ConversationControl(const ConversationControl &) = delete;
    ConversationControl operator=(const ConversationControl &) = delete;

    static bool isConversationRunning_;

private:
    void getMessage();
    bool isMessagesToReadExist();
    void handleInterlocutorInactivity();
    void markUserInactivityAsHandled();
    void reciveMessage();
    void sendMessage();
    void stopThreads();
    void startThreads();
    void saveMessageToDisplay();

    std::shared_ptr<ChatInformation> _chatInfo;
    std::unique_ptr<Sender> _sender;
    std::unique_ptr<Receiver> _receiver;
    std::unique_ptr<std::thread> _getMessageToQueueThread;
    std::unique_ptr<std::thread> _sendMessageFromQueueThread;
    std::unique_ptr<std::thread> _reciveMessageThread;
    std::queue<Message> _messageReadyToSend;
    std::queue<PurgeMessage> _messageToDisplay;
    bool _isThreadsRunning;
    bool _isUserInactivityWasHandled;
    UserInactivityDetector _userInactivityDetector;
    const SignalHandler& _signalHandler;
    const NcursesPrintOperationWrapper& _informationPrinter;

    Logger _log{LogSpace::ChatStarter};
};
