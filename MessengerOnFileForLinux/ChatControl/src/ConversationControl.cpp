
#include <ConversationControl.hpp>

#include <chrono>
#include <thread>
#include <stdio.h>

#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <SignalHandling.hpp>
#include <ChatWindow.hpp>
#include <ConsoleWindow.hpp>

ConversationControl::ConversationControl(const std::string& chatFileWithPath, std::string messageFlag)
    : chatFileWithPath_(chatFileWithPath)
    , messageFlag_(messageFlag)
{
    log.info("ChatControl C-TOR ");
    getMessageToQueueThread_ = nullptr;
    reciveMessageThread_ = nullptr;
    sendMessageFromQueueThread_ = nullptr;
}

ConversationControl::~ConversationControl()
{
    log.info("ChatControl D-TOR ");

    if (getMessageToQueueThread_ && reciveMessageThread_)
    {
        getMessageToQueueThread_->join();
        reciveMessageThread_->join();
        sendMessageFromQueueThread_->join();
    }
}

void ConversationControl::conversation()
{
    log.info("ChatControl::conversationControl started");
    std::signal(SIGINT, SignalHandling::sigintHandlerInChatConsole);
    ChatWindow::displayChatWindows();
    isThreadsRunning_ = true;
    startThreads();
}

void ConversationControl::conversationEpilog()
{
    log.info("ChatControl::endConversation started");
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
    log.info("ChatControl::getMessage started");
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, messageFlag_);
    while(isThreadsRunning_)
    {
        ChatWindow::displayEnterMessageWindow();
        messageReadyToSend_.push(sender->getMessageToSend());

        //auto convertedMessage = username + " >> " + message;
        auto convertedMessage = messageReadyToSend_.front().messageToSave();

        messageToDisplay_.push(convertedMessage);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool ConversationControl::isMessagesToReadExist()
{
    auto chatFolder = *FileInterface::Accesor::getFolderName(chatFileWithPath_);

    if(MessageFlag::inviterMessage == messageFlag_)
    {
        return FileInterface::Managment::isFileExist(chatFolder + "/NEW_" + MessageFlag::recipientMessage);
    }
    else if(MessageFlag::recipientMessage == messageFlag_)
    {
        return FileInterface::Managment::isFileExist(chatFolder + "/NEW_" + MessageFlag::inviterMessage);
    }
}

void ConversationControl::reciveMessage()
{
    log.info("ChatControl::reciveMessage started");

    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>(chatFileWithPath_, messageFlag_);

    while(isThreadsRunning_)
    {
        if (!messageToDisplay_.empty())
        {
            ChatWindow::displayDisplayMessageWindow(messageToDisplay_.front() + "\n");
            messageToDisplay_.pop();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        if (isMessagesToReadExist())
        {
            receiver->readMessagesToStack();
            saveMessageToDisplay(receiver);
        }
    }
}

void ConversationControl::sendMessage()
{
    log.info("ChatControl::sendMessage started");

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, messageFlag_);
    while(isThreadsRunning_ || !messageReadyToSend_.empty())
    {
        if (messageReadyToSend_.empty())
        {
            sleep(1);
        }
        else
        {
            sender->sendMessage(messageReadyToSend_.front());
            messageReadyToSend_.pop();
        }
    }
}

void ConversationControl::startThreads()
{
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

void ConversationControl::saveMessageToDisplay(const std::unique_ptr<Receiver>& receiver)
{
    bool isEndOfMessages = false;
    while(!isEndOfMessages)
    {
        auto message = receiver->returnTheOldestMessage();
        if("" == message)
        {
            isEndOfMessages = true;
        }
        else
        {
            messageToDisplay_.push(message);
        }
    }
}

void ConversationControl::stopThreads()
{
    isThreadsRunning_ = false;
}

