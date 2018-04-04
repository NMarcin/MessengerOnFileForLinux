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
        startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
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

void ChatControl::startConversationAsInviter(const std::string& username)
{
    ChatRequest chatRequest;
    bool isInviteAccepted = chatRequest.sendChatRequest(username);
    if(isInviteAccepted)
    {
        messageFlag_ = MessageFlag::inviterMessage;
        conversationControl();
    }
}

void ChatControl::startConversationAsRecipient(const int pid)
{
    ChatRequest chatRequest;
    bool isInviteAccepted = chatRequest.answerForChatRequest(pid);
    if(isInviteAccepted)
    {
        messageFlag_ = MessageFlag::recipientMessage;
        conversationControl();
    }
}


void ChatControl::conversationControl()
{
    //TODO mwozniak zmienic na make_unique
    *getMessageThread_ = std::thread([&](){
        std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFilenameWithPath_, static_cast<int>(messageFlag_));
        while(isThreadsRunning_)
        {
            //TODO jestli cos wysle to koniec rozmowy
            messageWaitingRoom_.push(sender->getMessageToSend());
        }
    });

    *reciverThread_ = std::thread([&](){
        std::unique_ptr<Reciver> reciver = std::make_unique<Reciver>();
        while(isThreadsRunning_)
        {
            //reciver_->recive()
            //TODO jesli cos odczyta to koniec rozmowy
            sleep(1);
        }
    });

    *sendMessageThread_ = std::thread([&](){
        std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFilenameWithPath_, static_cast<int>(messageFlag_));
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
    });

}
