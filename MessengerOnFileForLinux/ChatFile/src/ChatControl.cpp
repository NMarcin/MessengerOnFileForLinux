#include <ChatControl.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

ChatControl::ChatControl(const std::string& username)
{
    std::string folderName = *findChatFolder(username);
    std::string fileName = *findChatFile(folderName);
    pathToChatFile_ = ENIVRONMENTAL_PATH::PATH_TO_FOLDER::CHATS_PATH + folderName + "/" + fileName;
    sender_ = std::make_unique<Sender>();
    reciver_ = std::make_unique<Reciver>();
}

ChatControl::~ChatControl()
{
    //NOOP
}

std::unique_ptr<std::string> ChatControl::findChatFolder(const std::string& username)
{
    std::string possibleFolderName_1 = username + "_" + LocalUser::getLocalUser().getUsername();
    std::string possibleFolderName_2 = LocalUser::getLocalUser().getUsername() + "_" + username;
    std::string command_1 = "ls " + static_cast<std::string>(ENIVRONMENTAL_PATH::PATH_TO_FOLDER::CHATS_PATH) + " | grep " + possibleFolderName_1;
    std::string command_2 = "ls " + static_cast<std::string>(ENIVRONMENTAL_PATH::PATH_TO_FOLDER::CHATS_PATH) + " | grep " + possibleFolderName_2;

    std::unique_ptr<std::string> folderName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command_1));

    if (!folderName->empty())
    {
        chatRole_ = ChatRole::inviting;
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

std::unique_ptr<std::string> ChatControl::findChatFile(const std::string& folderName)
{
    std::unique_ptr<std::string> fileName = std::make_unique<std::string>(folderName);
    auto it = fileName->begin();
    while (isdigit(*it))
    {
        fileName->erase(it);
    }

    return fileName;
}

bool ChatControl::sendMessage() const
{
    return sender_->sendMessage(pathToChatFile_, static_cast<int>(chatRole_));
}

bool ChatControl::reciveMessage() const
{
    //return reciver_->reciveMesage(pathToChatFile_);
    return true;
}
