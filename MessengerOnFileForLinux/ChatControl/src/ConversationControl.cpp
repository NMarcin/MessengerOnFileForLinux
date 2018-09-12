
#include <ConversationControl.hpp>

#include <chrono>
#include <thread>
#include <stdio.h>

#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <Display.hpp>
#include <SignalHandling.hpp>
#include <ChatWindow.hpp>

ConversationControl::ConversationControl(const std::string& chatFileWithPath, MessageFlag messageFlag)
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
    delwin(ChatWindow::getEnterMessageWindow());
    delwin(ChatWindow::getDisplayMessageWindow());
    Display::displayMainWindow();

    //TODO mawoznia dalsza czesc konczenia rozmowe, pobieranie historii itd.
    //zastanowic sie co z usuwaniem pliku rozmowy
    const std::string userActiveStatus = "0";
    const std::string username = LocalUser::getLocalUser().getUsername();
    FileInterface::Modification::updateRowField(ENVIRONMENT_PATH::TO_FILE::LOGGED, username, userActiveStatus, FileStructure::LoggedFile::status);
}

void ConversationControl::getMessage()
{
    log.info("ChatControl::getMessage started");
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, static_cast<int>(messageFlag_));
    while(isThreadsRunning_)
    {
        ChatWindow::displayEnterMessageWindow();
        messageReadyToSend_.push(sender->getMessageToSend());

        auto username = *FileInterface::Accesor::getRowField(messageReadyToSend_.front(), FileStructure::MessageFile::username);
        auto message = *FileInterface::Accesor::getRowField(messageReadyToSend_.front(), FileStructure::MessageFile::message);
        auto convertedMessage = username + " >> " + message;

        messageToDisplay_.push(convertedMessage);

        std::this_thread::sleep_for(std::chrono::milliseconds(50+static_cast<int>(messageFlag_)));
    }
}

void ConversationControl::reciveMessage()
{
    log.info("ChatControl::reciveMessage started");

    auto messageFlag = std::to_string(static_cast<int>(messageFlag_));
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>(chatFileWithPath_, messageFlag);

    while(isThreadsRunning_)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30+static_cast<int>(messageFlag_)));

        log.info("PRZED1");
        receiver->readMessagesToStack();
        bool isEndOfMessages = false;
        log.info("PRZED");
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
        log.info("PO");
        if (!messageToDisplay_.empty())
        {
            std::string message = *FileInterface::Accesor::getRowField(messageToDisplay_.front(), 3);
            log.info(("ChatControl::reciveMessage Receive ===" + message + "===").c_str());
            if (5 <= message.size() && "//end" == std::string(message.begin(), message.begin()+5))
            {
                //TODO mawoznia narzucic tu implementacje z terminal funcionality
                log.info("ChatControl::reciveMessage Receive 'end conversatoin' request");
                messageToDisplay_.pop();
                conversationEpilog();
            }
            else if (2 <= message.size() && "//" == std::string(message.begin(), message.begin()+2))
            {
                log.info("ChatControl::reciveMessage Receive 'terminal funcionality' request");
                //TODO mawoznia co chcemy jeszcze wywolywac bezposrednio z czatu ?
                messageToDisplay_.pop();
            }
            else
            {
                log.info("ChatControl::reciveMessage Receive messageeeeeeeeeee");
                ChatWindow::displayDisplayMessageWindow( messageToDisplay_.front() + "\n");
                messageToDisplay_.pop();
            }
        }
    }
}

void ConversationControl::sendMessage()
{
    log.info("ChatControl::sendMessage started");

    std::this_thread::sleep_for(std::chrono::milliseconds(10+static_cast<int>(messageFlag_)));

    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, static_cast<int>(messageFlag_));
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

void ConversationControl::stopThreads()
{
    isThreadsRunning_ = false;
}

