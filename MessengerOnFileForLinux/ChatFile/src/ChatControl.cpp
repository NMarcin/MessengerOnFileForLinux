#include <chrono>
#include <thread>

#include <ChatControl.hpp>
#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

ChatControl::ChatControl()
{
    getMessageThread_ = nullptr;
    reciverThread_ = nullptr;
    sendMessageThread_ = nullptr;
}

ChatControl::~ChatControl()
{
    //NOOP
}

void ChatControl::startConversation(const std::string& username, ChatRole chatRole)
{
    if (ChatRole::inviter == chatRole)
    {
        std::cout << "inviter" << std::endl;
        startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
        std::cout << "recipent" << std::endl;
        int usernamePid = std::atoi(username.c_str());
        startConversationAsRecipient(usernamePid);
    }
}

void ChatControl::endConversation()
{
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
    isThreadsRunning_ = false;
}

void ChatControl::getMessage()
{
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, static_cast<int>(messageFlag_));
    while(isThreadsRunning_)
    {
        //TODO jestli cos wysle to koniec rozmowy
        messageWaitingRoom_.push(sender->getMessageToSend());
    }
}

void ChatControl::reciveMessage()
{
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
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.sendChatRequest(username);
    std::cout << chatFileWithPath_ << std::endl;
    if(!chatFileWithPath_.empty())
    {
        messageFlag_ = MessageFlag::inviterMessage;
        conversationControl();
    }
}

void ChatControl::startConversationAsRecipient(const int pid)
{
    ChatRequest chatRequest;
    chatFileWithPath_ = chatRequest.answerForChatRequest(pid);
    std::cout << "Recipent: " << chatFileWithPath_ << std::endl;
    if(!chatFileWithPath_.empty())
    {
        messageFlag_ = MessageFlag::recipientMessage;
        conversationControl();
    }
}


void ChatControl::conversationControl() // TODO mwozniak lambdy -> funkcje
{
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
