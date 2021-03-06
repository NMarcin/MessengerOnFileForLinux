#pragma once
#include <stack>
#include <queue>
#include <string>
#include <memory>

#include "Logger.hpp"
#include "LogSpace.hpp"
#include "PurgeMessage.hpp"
#include "TerminalFunctionality.hpp"

class Receiver
{
public:
    Receiver(std::shared_ptr<ChatInformation> chatInfo);
    ~Receiver() = default;

    Receiver(Receiver &&) = delete;
    Receiver operator=(Receiver &&) = delete;
    Receiver(const Receiver &) = delete;
    Receiver operator=(const Receiver &) = delete;

    bool readMessagesToStack();
    std::unique_ptr<PurgeMessage> returnTheOldestMessage();

private:
    bool updateSeenFlags();
    bool endOfMessageToRead(std::string message, std::string messageFlag);
    bool isChatFileEmpty(std::unique_ptr<std::vector<std::string>>& chatFileContent);
    void pushPurgeMessageOnStack(std::string rawMessageToPush);
    std::unique_ptr<PurgeMessage> messagePurging(Message& messageToPurge);
    void removeFlagNEW();

    std::shared_ptr<ChatInformation> _chatInfo;
    std::stack<PurgeMessage> _purgeMessagesStack;

    Logger _log{LogSpace::ChatControl};
};
