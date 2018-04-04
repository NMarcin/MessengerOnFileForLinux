#include <chrono>
#include <thread>

#include <ChatControl.hpp>
#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

ChatControl::ChatControl()
{
    senderThread_ = nullptr;
    reciverThread_ = nullptr;
    sendMessage_ = nullptr;
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
{//TODO czy to sie nie posypie ?
    if (senderThread_ && reciverThread_)
    {
        senderThread_->join();
        reciverThread_->join();
        sendMessage_->join();
    }

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
        //setPathToChatFile(username);
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
    *senderThread_ = std::thread([&](){
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

    *sendMessage_ = std::thread([&](){
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

/*
std::unique_ptr<std::string> ChatControl::getChatFoldername(const std::string& username)
{
    std::string possibleFolderName_1 = username + "_" + LocalUser::getLocalUser().getUsername();
    std::string possibleFolderName_2 = LocalUser::getLocalUser().getUsername() + "_" + username;
    std::string command_1 = "ls " + ENIVRONMENT_PATH::PATH_TO_FOLDER::CHATS_FOLDER + " | grep " + possibleFolderName_1;
    std::string command_2 = "ls " + ENIVRONMENT_PATH::PATH_TO_FOLDER::CHATS_FOLDER + " | grep " + possibleFolderName_2;

    std::unique_ptr<std::string> folderName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command_1));

    if (!folderName->empty())
    {
        folderName->pop_back(); //usuwanie znaku konca lini
        return folderName;
    }

    folderName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command_2));

    if (!folderName->empty())
    {
        folderName->pop_back();
        return folderName;
    }

    return nullptr;
}

std::unique_ptr<std::string> ChatControl::getChatFilename(const std::string& folderName)
{
    std::unique_ptr<std::string> fileName = std::make_unique<std::string>(folderName);
    auto it = fileName->begin();
    while (isdigit(*it))
    {
        fileName->erase(it);
    }

    return fileName;
}
*/

/*
void Sender::sendMessageFromWaitingRoom()
{
    while (!isMessageWaitngRoomEmpty_)
    {
        if (messageWaitngRoom_.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else
        {
            std::unique_ptr<std::string> messageToSend = std::move(messageWaitngRoom_.front());
            bool isMessageSent = FileInterface::Modification::addRow(pathToChatFile_, *messageToSend);

            if (isMessageSent)
            {
                std::unique_ptr<std::string> folderName = FileInterface::Accesor::getFolderName(pathToChatFile_);
                setNewMessageFlag(*folderName);
                messageWaitngRoom_.pop();
            }
        }
    }
}
*/













