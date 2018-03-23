#include <ChatControl.hpp>
#include <FileHandling.hpp>
#include <ChatRequest.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

ChatControl::ChatControl()
{
    //NOOP
}

ChatControl::~ChatControl()
{
    senderThread.join();
    reciverThread.join();
}

std::unique_ptr<std::string> ChatControl::getChatFolderName(const std::string& username)
{
    std::string possibleFolderName_1 = username + "_" + LocalUser::getLocalUser().getUsername();
    std::string possibleFolderName_2 = LocalUser::getLocalUser().getUsername() + "_" + username;
    std::string command_1 = "ls " + static_cast<std::string>(ENIVRONMENT_PATH::PATH_TO_FOLDER::CHATS_FOLDER) + " | grep " + possibleFolderName_1;
    std::string command_2 = "ls " + static_cast<std::string>(ENIVRONMENT_PATH::PATH_TO_FOLDER::CHATS_FOLDER) + " | grep " + possibleFolderName_2;

    std::unique_ptr<std::string> folderName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command_1));

    if (!folderName->empty())
    {
        chatRole_ = ChatRole::inviter;
        folderName->pop_back(); //usuwanie znaku konca lini
        return folderName;
    }

    folderName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command_2));

    if (!folderName->empty())
    {
        chatRole_ = ChatRole::respondent;
        folderName->pop_back();
        return folderName;
    }

    return nullptr;
}

std::unique_ptr<std::string> ChatControl::getChatFileName(const std::string& folderName)
{
    std::unique_ptr<std::string> fileName = std::make_unique<std::string>(folderName);
    auto it = fileName->begin();
    while (isdigit(*it))
    {
        fileName->erase(it);
    }

    return fileName;
}

void ChatControl::setChatPathWithFile(const std::string& username)
{
    std::string folderName = *getChatFolderName(username);
    std::string fileName = *getChatFileName(folderName);
    std::string chatPathWithFile = ENIVRONMENT_PATH::PATH_TO_FOLDER::CHATS_FOLDER + folderName + "/" + fileName;
    pathToChatFile_ = chatPathWithFile;
}


void ChatControl::startConversationAsInviter(const std::string& username)
{
    ChatRequest chatRequest;
    bool isInviteAccepted = chatRequest.sendChatRequest(username);
    if(isInviteAccepted)
    {
        setChatPathWithFile(username);
        conversationControl();
    }
}

void ChatControl::startConversationAsRespondent(const int pid)
{
    ChatRequest chatRequest;
    bool isInviteAccepted = chatRequest.answerForChatRequest(pid);
    if(isInviteAccepted)
    {
        std::unique_ptr<std::string> username = chatRequest.getUsernameThroughPid(pid);
        setChatPathWithFile(*username);
        conversationControl();
    }
}

void ChatControl::conversationControl()
{
    senderThread = std::thread([&](){
        std::unique_ptr<Sender> sender_ = std::make_unique<Sender>();

        while(isChatRunning)
        {
            sender_->sendMessage(pathToChatFile_, 1);
            std::cout << " T1 " << std::endl;
            sleep(1);
        }
    });

    reciverThread = std::thread([&](){
        int k = 0;
        std::unique_ptr<Reciver> reciver_ = std::make_unique<Reciver>();
        while(isChatRunning)
        {
            //reciver_->recive()
            std::cout << " T2 " << std::endl;
            sleep(1);
        }
    });


}

void ChatControl::endConversation()
{
    isChatRunning = false;
    //TODO mwozniak mozliwosc pobrania histori rozmowy
    std::cout << "KONCZE CZAT" << std::endl;
}















