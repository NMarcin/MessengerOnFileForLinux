#include <iostream>
#include <signal.h>
#include <algorithm>

#include <ChatRequest.hpp>
#include <User.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <ChatFabric.hpp>
#include <Display.hpp>

ChatRequest::ChatRequest()
{
    initscr();
    log.info("ChatRequest C-TOR");
}

ChatRequest::~ChatRequest()
{
    endwin();
    log.info("ChatRequest D-TOR");
}

std::string ChatRequest::answerForChatRequest(const std::string& senderUsername) const
{
    log.info("ChatRequest::answerForChatRequest started");
    std::string invitationName =  LocalUser::getLocalUser().getUsername() + "_" + senderUsername;
    FileInterface::Managment::removeFile(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS + invitationName);
    showInvitation(senderUsername);
    bool decision = approveChatInvitation();

    if (decision)
    {
        return sendAnswer(senderUsername, AnswerType::accepted);
    }

    return sendAnswer(senderUsername, AnswerType::disaccepted);
}

bool ChatRequest::changeUserStatus(const User& user, const std::string& newStatus) const    // TODO mnurzyns mwozniak po zmianie fora sprawdzic
{
    log.info("ChatRequest::changeUserStatus started");

    auto username = user.getUsername();
    return FileInterface::Modification::updateRowField(ENVIRONMENT_PATH::TO_FILE::LOGGED, username, newStatus, FileStructure::LoggedFile::status);

}

std::unique_ptr<std::string> ChatRequest::getChatFolderName(const std::string& folderName) const
{
    log.info("ChatRequest::getChatFolderName started");
    std::string command= "ls " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + " | grep " + folderName;
    std::unique_ptr<std::string> folderFullName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command));
    std::string logData = "ChatRequest::getChatFolderName -> " + *folderFullName;
    log.info(logData.c_str());
     if (!folderFullName->empty())
     {
         return folderFullName ;
     }

     return nullptr;
}

std::unique_ptr<std::string> ChatRequest::getUserStatus(const std::string& username) const
{
    log.info("ChatRequest::getUserStatus started");

    auto row = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, username);
    if (row)
    {
        std::unique_ptr<std::string> userStatus = FileInterface::Accesor::getRowField(*row, FileStructure::LoggedFile::status);
        return userStatus;
    }

    log.info("ChatRequest::getUserStatus ERROR: User is offline or does not exist");
    printw("User is offline or does not exist.");
    refresh();

    return nullptr;
}


bool ChatRequest::isUserActive(const User& user) const
{
    log.info("ChatRequest::isUserActive started");
    std::unique_ptr<std::string> userStatusToCompare = getUserStatus(user.getUsername());

    if (nullptr == userStatusToCompare)
    {
        return false;
    }

    if (!UserStatus::activeStatus.compare(*userStatusToCompare)) //0 when succes
    {
        return true;
    }

    log.info("ChatRequest::isUserActive ERROR: User is bussy");
    printw("User is bussy. Try again later.");
    refresh();

    return false;
}

bool ChatRequest::approveChatInvitation() const
{
    log.info("ChatRequest::approveChatInvitation started");
    std::string decision;
    //decision = Display::getStringFromMainWindow(); //TODO mwoznia PROBLEM Z UT
    std::cin >> decision;
    std::transform(decision.begin(), decision.end(), decision.begin(), ::tolower);

    if ("y" == decision || "yes" == decision)
    {
        log.info("ChatRequest::approveChatInvitation Invitation accepted");
        return true;
    }
    else if ("n" == decision || "no" == decision)
    {
        log.info("ChatRequest::approveChatInvitation Invitation disaccepted");
        return false;
    }

    log.info("ChatRequest::approveChatInvitation Invitation disaccepted. Timeout while waiting for answer");
    return false; //TODO mwozniak co jesli wprawdzi inna odpwiedz (może for na 5 iteracji)
}

std::string ChatRequest::sendAnswer(const std::string& senderUsername, AnswerType type) const
{
    log.info("ChatRequest::sendAnswer started");
    std::string folderNameWithoutNumber = senderUsername + "_" + LocalUser::getLocalUser().getUsername();
    std::string folderFullName = *getChatFolderName(folderNameWithoutNumber);
    std::string flagPath = ENVIRONMENT_PATH::TO_FOLDER::CHATS + folderFullName;

    if (AnswerType::disaccepted == type)
    {
        FileInterface::Managment::createFile(flagPath + "/DISACCEPTED");
    }
    else if (AnswerType::accepted == type)
    {
        FileInterface::Managment::createFile(flagPath + "/ACCEPTED");
        std::string chatFilename = folderNameWithoutNumber;
        return flagPath + "/" + chatFilename;
    }
    return "";
}

std::string ChatRequest::sendChatRequest(const std::string& username) const
{
    log.info("ChatRequest::sendChatRequest started");
    User receiver(username);
    changeUserStatus(LocalUser::getLocalUser().getUsername(), UserStatus::bussyStatus);
    //^ przez ta linijke są zakomentowane UT

    ChatFabric chatFabric;
    std::string chatFileWithPath = chatFabric.createChatStructure(LocalUser::getLocalUser().getUsername(), receiver.getUsername());

    if (!isUserActive(receiver.getUsername()))  // TODO mwozniak polaczyc z ChatFabric w ifie, usunac !, a else return {}
    {
        return {};
    }
    changeUserStatus(receiver.getUsername(), UserStatus::bussyStatus);

    std::string invitationName = username + "_" + LocalUser::getLocalUser().getUsername();
    FileInterface::Managment::createFile(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS + invitationName);

    bool receiverDecision = waitForAnswer(receiver.getUsername());
    if(receiverDecision)
    {
        return chatFileWithPath;
    }

    auto chatFileFolder = *FileInterface::Accesor::getFolderName(chatFileWithPath);
    FileInterface::Managment::removeFile(chatFileFolder);
    changeUserStatus(LocalUser::getLocalUser().getUsername(), UserStatus::activeStatus);
    changeUserStatus(receiver.getUsername(), UserStatus::activeStatus);
    return {};

}

void ChatRequest::showInvitation(const std::string& senderUsername) const
{
    log.info("ChatRequest::showInvitation started");
    clear();
    printw(("You get an invitation to chat form " + senderUsername + "\n").c_str());
    printw("Do you want to chat with this user (y/n)? \n");
    printw(">> ");
    refresh();
}

bool ChatRequest::waitForAnswer(const std::string& username) const
{
    log.info("ChatRequest::waitForAnswer started");
    std::string folderName = LocalUser::getLocalUser().getUsername() + "_" + username;
    std::string folderFullName = *getChatFolderName(folderName);

    const int timeToWaitForAnswer = 20;
    const std::string flagPath = ENVIRONMENT_PATH::TO_FOLDER::CHATS + folderFullName;

    for (int i = 0; i < timeToWaitForAnswer; i++)
    {
        if (FileInterface::Managment::isFileExist(flagPath + "/ACCEPTED"))
        {
            std::cout << username + " has accepted the invitation. Send Hello!" << std::endl;
            FileInterface::Managment::removeFile(flagPath + "/ACCEPTED");
            return true;
        }
        else if (FileInterface::Managment::isFileExist(flagPath + "/DISACCEPTED"))
        {
            std::cout << "User has not accepted the invitation" << std::endl;
            FileInterface::Managment::removeFile(flagPath + "/DISACCEPTED");
            return false;
        }

        sleep(1);
    }

    log.info("ChatRequest::waitForAnswer ERROR: User has not accepted the invitation");
    std::cout << "User has not accepted the invitation." << std::endl;
    return false;
}
