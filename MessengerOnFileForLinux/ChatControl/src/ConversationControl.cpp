
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

ConversationControl::ConversationControl(std::shared_ptr<ChatInformation> chatInfo)
    : chatInfo_(chatInfo)
{
    log.info("ChatControl C-TOR ");
    getMessageToQueueThread_ = nullptr;
    reciveMessageThread_ = nullptr;
    sendMessageFromQueueThread_ = nullptr;
    chatFileWithPath_ = chatInfo_->chatPath_;
    messageFlag_ = chatInfo_->messageFlag_;
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


        //auto messega = messageReadyToSend_.front().messageToSave();
        //auto convertedMessage = username + " >> " + message;
        // TODO mwozniak nie jestem pewny czy zrozumialem o co tutaj chodzi
        // czym jest convertedMessage? z tego co ja rozumiem to sluzy do
        // wystwietlania wiadomosci przez uzytkownika ktory ja napisal u niego
        //auto x = convertedMessage.messageToShow();
        log.info("DUPA");
        //log.info(x);
        auto ownMessageToDisplay = PurgeMessage(messageReadyToSend_.front());
        ownMessageToDisplay.messageToShow();
        messageToDisplay_.push(ownMessageToDisplay);

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
            ChatWindow::displayDisplayMessageWindow(messageToDisplay_.front().messageToShow() + "\n");
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

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    auto elapsedTime = std::chrono::milliseconds(20);


    log.info(chatFileWithPath_);
    log.info(messageFlag_);
    log.info("ChatControl::sendMessage PODSUMOWANIE");
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, messageFlag_);

    while(isThreadsRunning_ || !messageReadyToSend_.empty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        elapsedTime +=  std::chrono::milliseconds(10);
        if (elapsedTime >= std::chrono::milliseconds(15000))
        {
            //TODO mawoznia spradz czy jest czat
            elapsedTime = std::chrono::milliseconds(0);
        }
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

void ConversationControl::saveMessageToDisplay(const std::unique_ptr<Receiver>& receiver)
{
    bool isEndOfMessages = false;
    while(!isEndOfMessages)
    {
        auto message = receiver->returnTheOldestMessage();
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
