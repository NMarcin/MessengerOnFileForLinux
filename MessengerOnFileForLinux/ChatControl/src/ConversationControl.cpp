#include <chrono>
#include <thread>
#include <stdio.h>

#include <ConversationControl.hpp>
#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <SignalHandling.hpp>
#include <ChatWindow.hpp>
#include <ConsoleWindow.hpp>
#include <PurgeMessage.hpp>

bool ConversationControl::isConversationRunning_ = false;

ConversationControl::ConversationControl(std::shared_ptr<ChatInformation> chatInfo)
    : chatInfo_(chatInfo)
    , sender_(std::make_unique<Sender>(chatInfo))
    , receiver_(std::make_unique<Receiver>(chatInfo))
    , getMessageToQueueThread_(nullptr)
    , reciveMessageThread_(nullptr)
    , sendMessageFromQueueThread_(nullptr)
    , userInactivityDetector_(chatInfo->interlocutorUsername_)
    , isUserInactivityWasHandled_(false)
{
    log_.function("ChatControl C-TOR ");
    isConversationRunning_ = true;
}

ConversationControl::~ConversationControl()
{
    log_.function("ChatControl D-TOR ");

    if (getMessageToQueueThread_ && reciveMessageThread_)
    {
        getMessageToQueueThread_->join();
        reciveMessageThread_->join();
        sendMessageFromQueueThread_->join();
    }
}

void ConversationControl::conversation()
{
    log_.function("ChatControl::conversationControl() started");
    SignalHandling::createPosixSignalsHandling(SignalHandling::posixSignalHandlerInChatConsole);
    ChatWindow::displayChatWindows();
    startThreads();
    while (isConversationRunning_)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void ConversationControl::conversationEpilog()
{
    log_.function("ChatControl::endConversation() started");
    stopThreads();

    ChatWindow::deleteDisplayMesageWindow();
    ChatWindow::deleteEnterMesageWindow();
    ConsoleWindow::displayMainWindow();

    const std::string userActiveStatus = "0";
    const std::string username = LocalUser::getLocalUser().getUsername();
    FileInterface::Modification::updateRowField(ENVIRONMENT_PATH::TO_FILE::LOGGED, username, userActiveStatus, FileStructure::LoggedFile::status);
}

void ConversationControl::getMessage()
{
    log_.function("ChatControl::getMessage() started");

    while(isThreadsRunning_)
    {
        ChatWindow::displayEnterMessageWindow();
        if (isConversationRunning_)
        {
            auto message = sender_->getMessageToSend();
            if(message)
            {
                messageReadyToSend_.push(*message);
            }
            else
            {
                continue;
            }

            PurgeMessage ownMessageToDisplay(messageReadyToSend_.front());
            messageToDisplay_.push(ownMessageToDisplay);
        }
        log_.debug("ChatControl::getMessage() isConversationRunning_ = false");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool ConversationControl::isMessagesToReadExist()
{
    auto chatFolder = *FileInterface::Accesor::getFolderName(chatInfo_->chatPath_);

    if(MessageFlag::inviterMessage == chatInfo_->messageFlag_)
    {
        return FileInterface::Managment::isFileExist(chatFolder + "/NEW_" + MessageFlag::recipientMessage);
    }
    else if(MessageFlag::recipientMessage == chatInfo_->messageFlag_)
    {
        return FileInterface::Managment::isFileExist(chatFolder + "/NEW_" + MessageFlag::inviterMessage);
    }
    return false;
}

void ConversationControl::handleInterlocutorInactivity()
{
    if(not isUserInactivityWasHandled_)
    {
        markUserInactivityAsHandled();
        const std::string pathToChatFolder = *FileInterface::Accesor::getFolderName(chatInfo_->chatPath_);
        const std::string systemMessage = "Your interlocutor is inactive! You can leve chat";
        Message message(chatInfo_->messageFlag_, "_SYSTEM_", systemMessage);
        sender_->sendMessage(message);
        messageToDisplay_.push(message);
        FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, chatInfo_->interlocutorUsername_);
        FileInterface::Managment::createFile(pathToChatFolder + "/END");
    }
}

void ConversationControl::markUserInactivityAsHandled()
{
    isUserInactivityWasHandled_ = true;
}

void ConversationControl::reciveMessage()
{
    log_.function("ChatControl::reciveMessage() started");

    while(isThreadsRunning_)
    {
        userInactivityDetector_.detectUserInactivity();

        if (!messageToDisplay_.empty())
        {
            ChatWindow::displayDisplayMessageWindow(messageToDisplay_.front().messageToShow() + "\n");
            messageToDisplay_.pop();
        }
        else if (userInactivityDetector_.isUserInactiveDetected())
        {
            handleInterlocutorInactivity();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        if (isMessagesToReadExist())
        {
            receiver_->readMessagesToStack();
            saveMessageToDisplay();
        }
    }
}

void ConversationControl::sendMessage()
{
    log_.function("ChatControl::sendMessage() started");
    while(isThreadsRunning_ || !messageReadyToSend_.empty())
    {
        if (messageReadyToSend_.empty())
        {
            sleep(1);
        }
        else
        {
            sender_->sendMessage(messageReadyToSend_.front());
            messageReadyToSend_.pop();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void ConversationControl::startThreads()
{
    log_.function("ChatControl::startThreads() started");
    isThreadsRunning_ = true;

    getMessageToQueueThread_ = std::make_unique<std::thread>(std::thread([&]()
    {
        getMessage();
    }));

    reciveMessageThread_ = std::make_unique<std::thread>(std::thread([&]()
    {
        reciveMessage();
    }));

    sendMessageFromQueueThread_ = std::make_unique<std::thread>(std::thread([&]()
    {
        sendMessage();
    }));
}

void ConversationControl::saveMessageToDisplay()
{
    log_.function("ChatControl::saveMessageToDisplay() started");
    bool isEndOfMessages = false;
    while(!isEndOfMessages)
    {
        auto message = receiver_->returnTheOldestMessage();
        if(nullptr == message)
        {
            isEndOfMessages = true;
        }
        else
        {
            messageToDisplay_.push(*message);
        }
    }
}

void ConversationControl::stopThreads()
{
    log_.function("ChatControl::stopThreads() started");
    isThreadsRunning_ = false;
}
