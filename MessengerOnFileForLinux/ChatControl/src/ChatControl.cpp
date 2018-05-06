#include <chrono>
#include <thread>

#include <ChatControl.hpp>
#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <Display.hpp>

ChatControl::ChatControl()
{
    log.info("ChatControl C-TOR ");
    getMessageToQueueThread_ = nullptr;
    reciveMessageThread_ = nullptr;
    sendMessageFromQueueThread_ = nullptr;
}

ChatControl::~ChatControl()
{
    log.info("ChatControl D-TOR ");

    if (getMessageToQueueThread_ && reciveMessageThread_)
    {
        getMessageToQueueThread_->join();
        reciveMessageThread_->join();
        sendMessageFromQueueThread_->join();
    }
}

void ChatControl::conversationProlog(const std::string& username, ChatRole chatRole)
{
    log.info("ChatControl::startConversation started");
    if (ChatRole::inviter == chatRole)
    {
        startConversationAsInviter(username);
    }
    else if (ChatRole::recipient == chatRole)
    {
        startConversationAsRecipient(username);
    }
}

void ChatControl::conversationEpilog()
{
    log.info("ChatControl::endConversation started");
    stopThreads();
    delwin(subwindow2);
    delwin(subwindow1);
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
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, static_cast<int>(messageFlag_), subwindow2);
    while(isThreadsRunning_)
    {
        //TODO jestli cos wysle to koniec rozmowy
        wclear(subwindow2);
        box(subwindow2, 0, 0);
        wmove(subwindow2, 1, 1);
        wrefresh(subwindow2);

        messageWaitingRoom_.push(sender->getMessageToSend());

        /*testownie. potem usunac */
        auto tmp = *messageWaitingRoom_.front();
        messageToDisplay_.push(tmp);
    }
}

void ChatControl::reciveMessage()
{
    log.info("ChatControl::reciveMessage started");
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();


    while(isThreadsRunning_)
    {
        sleep(1);
        //reciver->recive()
        //TODO jesli cos odczyta to koniec rozmowy
        if (!messageToDisplay_.empty())
        {
            wprintw(subwindow1, (messageToDisplay_.front() + "\n").c_str());
            box(subwindow1, 0, 0);
            wrefresh(subwindow1);
            messageToDisplay_.pop();
        }

    }
}

void ChatControl::sendMessage()
{
    log.info("ChatControl::sendMessage started");
    std::unique_ptr<Sender> sender = std::make_unique<Sender>(chatFileWithPath_, static_cast<int>(messageFlag_), subwindow2);
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
        conversation();
    }
    else
    {
        conversationEpilog();
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
        conversation();
    }
    else
    {
        conversationEpilog();
    }
}


void ChatControl::conversation()
{
    clear();
    subwindow1 = newwin(15,40,1,1);//size y,x; wspolrzedne startu
    subwindow2 = newwin(3,40,15,1);
    box(subwindow1,0,0);
    box(subwindow2,0,0);
    refresh();
    wrefresh(subwindow1);
    wrefresh(subwindow2);

    isThreadsRunning_ = true;

    log.info("ChatControl::conversationControl started");
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
