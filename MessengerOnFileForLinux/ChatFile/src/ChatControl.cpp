#include <chrono>
#include <thread>

#include <ChatControl.hpp>
#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

ChatControl::ChatControl()
{
    log.info("ChatControl C-TOR ");
    getMessageThread_ = nullptr;
    reciverThread_ = nullptr;
    sendMessageThread_ = nullptr;
}

ChatControl::~ChatControl()
{
    log.info("ChatControl D-TOR ");

    if (getMessageThread_ && reciverThread_)
    {
        getMessageThread_->join();
        reciverThread_->join();
        sendMessageThread_->join();
    }
}

void ChatControl::startConversation(const std::string& username, ChatRole chatRole)
{
    log.info("ChatControl::startConversation started");
    if (ChatRole::inviter == chatRole)
    {
        startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
        //int usernamePid = std::atoi(username.c_str());
        startConversationAsRecipient(username);
    }
}

void ChatControl::endConversation()
{
    log.info("ChatControl::endConversation started");
    stopThreads();

    if (getMessageThread_ && reciverThread_)
    {
        getMessageThread_->join();
        reciverThread_->join();
        sendMessageThread_->join();
    }

    //TODO dalsza czesc konczenia rozmowe, pobieranie historii itd.
}

void ChatControl::stopThreads()
{
    log.info("ChatControl::stopThreads started");
    isThreadsRunning_ = false;
}

void ChatControl::getMessage()
{
    log.info("ChatControl::getMessage started");
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, static_cast<int>(messageFlag_));
    while(isThreadsRunning_)
    {
        //TODO jestli cos wysle to koniec rozmowy
        messageWaitingRoom_.push(sender->getMessageToSend());
    }
}

void ChatControl::reciveMessage()
{
    log.info("ChatControl::reciveMessage started");
    std::unique_ptr<Reciver> reciver = std::make_unique<Reciver>();
    while(isThreadsRunning_)
    {
        //reciver->recive()
        //TODO jesli cos odczyta to koniec rozmowy
        sleep(1);
    }
}

void ChatControl::sendMessage()
{
    log.info("ChatControl::sendMessage started");
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, static_cast<int>(messageFlag_));
    while(isThreadsRunning_ || !messageWaitingRoom_.empty())
    {
        if (messageWaitingRoom_.empty())
        {
            sleep(1);
        }
        else
        {
            sender->sendMessage(*messageWaitingRoom_.front());
            messageWaitingRoom_.pop();
        }
    }
}

void ChatControl::startConversationAsInviter(const std::string& username)
{
    log.info("ChatControl::startConversationAsInviter started");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.sendChatRequest(username);
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsInviter chatFileWithPath_: " + chatFileWithPath_;
        log.info(info.c_str());
        messageFlag_ = MessageFlag::inviterMessage;
        conversationControl();
    }
    else
    {
        endConversation();
    }
}

void ChatControl::startConversationAsRecipient(const std::string& username)
{
    log.info("ChatControl::startConversationAsRecipient started");
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.answerForChatRequest(username);
    if(!chatFileWithPath_.empty())
    {
        std::string info = "ChatControl::startConversationAsRecipient chatFileWithPath_: " + chatFileWithPath_;
        log.info(info.c_str());
        messageFlag_ = MessageFlag::recipientMessage;
        conversationControl();
    }
    else
    {
        endConversation();
    }
}


void ChatControl::conversationControl()
{
    isThreadsRunning_ = true;
    log.info(("ChatControl::conversationControl started. Flag status: " + std::to_string(isThreadsRunning_)).c_str());
    getMessageThread_ = std::make_unique<std::thread>(std::thread([&]()
    {
        getMessage();
    }));

    reciverThread_ = std::make_unique<std::thread>(std::thread([&]()
    {
        reciveMessage();
    }));

    sendMessageThread_ = std::make_unique<std::thread>(std::thread([&]()
    {
        sendMessage();
    }));

}
