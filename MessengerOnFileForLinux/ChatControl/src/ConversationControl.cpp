
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
#include <PurgeMessage.hpp>

bool ConversationControl::isConversationRunning_ = false;

ConversationControl::ConversationControl(std::shared_ptr<ChatInformation> chatInfo)
    : chatInfo_(chatInfo)
    , sender_(std::make_unique<Sender>(chatInfo))
    , receiver_(std::make_unique<Receiver>(chatInfo))
    , getMessageToQueueThread_(nullptr)
    , reciveMessageThread_(nullptr)
    , sendMessageFromQueueThread_(nullptr)
{
    log.info("ChatControl C-TOR ");
    isConversationRunning_ = true;
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
    startThreads();
    while (isConversationRunning_)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
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
    while(isThreadsRunning_)
    {
        ChatWindow::displayEnterMessageWindow();
        messageReadyToSend_.push(sender_->getMessageToSend());

        auto ownMessageToDisplay = PurgeMessage(messageReadyToSend_.front());
        ownMessageToDisplay.messageToShow();
        messageToDisplay_.push(ownMessageToDisplay);

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
}

void ConversationControl::reciveMessage()
{
    log.info("ChatControl::reciveMessage started");

    while(isThreadsRunning_)
    {
        if (!messageToDisplay_.empty())
        {
            ChatWindow::displayDisplayMessageWindow(messageToDisplay_.front().messageToShow() + "\n");
            messageToDisplay_.pop();
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
    log.info("ChatControl::sendMessage started");

    auto beginTime = std::chrono::system_clock::now();
    auto newTime = std::chrono::system_clock::now();

    while(isThreadsRunning_ || !messageReadyToSend_.empty())
    {
        newTime = std::chrono::system_clock::now();
        auto timePeriod = newTime - beginTime;

        if (timePeriod >= std::chrono::seconds(15))
        {
            //TODO dalsza obsluga enda
            log.info("ChatControl::sendMessage looking for END flag");
            beginTime = std::chrono::system_clock::now();
        }
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
    isThreadsRunning_ = false;
}
