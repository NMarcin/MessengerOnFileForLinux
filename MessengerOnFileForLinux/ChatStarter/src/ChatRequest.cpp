#include <iostream>
#include <signal.h>
#include <algorithm>
#include <sstream>
#include <unistd.h>

#include "ChatRequest.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"
#include "LocalUser.hpp"
#include "ChatFabric.hpp"
#include "ConsoleWindow.hpp"

ChatRequest::ChatRequest()
{
    _log.function("ChatRequest C-TOR");
    initscr();
}

ChatRequest::~ChatRequest()
{
    _log.function("ChatRequest D-TOR");
    endwin();
}

std::string ChatRequest::answerForChatRequest(const std::string& senderUsername, const std::string& decision) const
{

    _log.function("ChatRequest::answerForChatRequest() started");
    if (decision == "accept") // obejscie problemu z czekaniem w petli
    {                         // TODO refacotr modulu jak rozwiazemy problem z czekaniem w petli na zaporszenie
        return sendAnswer(senderUsername, AnswerType::accepted);
    }
    return sendAnswer(senderUsername, AnswerType::disaccepted);

    std::string invitationName =  LOCAL_USER + "_" + senderUsername;
    FileInterface::Managment::removeFile(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS + invitationName);
    showInvitation(senderUsername);
    bool decisionStatus = approveChatInvitation();

    if (decisionStatus)
    {
        return sendAnswer(senderUsername, AnswerType::accepted);
    }

    return sendAnswer(senderUsername, AnswerType::disaccepted);
}

bool ChatRequest::changeUserStatus(const std::string& username, const std::string& newStatus) const
{
    _log.function("ChatRequest::changeUserStatus() started");

    return FileInterface::Modification::updateRowField(ENVIRONMENT_PATH::TO_FILE::LOGGED, username, newStatus, FileStructure::LoggedFile::status);
}

std::unique_ptr<std::string> ChatRequest::getChatFolderName(const std::string& folderName) const
{
    _log.function("ChatRequest::getChatFolderName() started");
    std::string command= "ls " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + " | grep " + folderName;
    std::unique_ptr<std::string> folderFullName = std::make_unique<std::string>(ConsolControl::getStdoutFromStartedCommand(command));
    std::string logData = "ChatRequest::getChatFolderName -> " + *folderFullName;
    _log.info(logData);
     if (!folderFullName->empty())
     {
         return folderFullName ;
     }

     return nullptr;
}

std::unique_ptr<std::string> ChatRequest::getUserStatus(const std::string& username) const
{
    _log.function("ChatRequest::getUserStatus() started");

    auto row = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, username);
    if (row)
    {
        std::unique_ptr<std::string> userStatus = FileInterface::Accesor::getRowField(*row, FileStructure::LoggedFile::status);
        return userStatus;
    }

    _log.info("ChatRequest::getUserStatus() ERROR: User is offline or does not exist");
    printw("User is offline or does not exist.");
    refresh();

    return nullptr;
}


bool ChatRequest::isUserActive(const std::string& username) const
{
    _log.function("ChatRequest::isUserActive() started");

    std::unique_ptr<std::string> userStatusToCompare = getUserStatus(username);

    UserInactivityDetector userInactivityDetector(username); //TODO mawoznia temportary solution
    userInactivityDetector.detectUserInactivity();       //it will be romoved in FB_03 in 'accepting and rejecting an invitation' task.
    if (userInactivityDetector.isUserInactiveDetected()) //UserInactivityDetector will be a member of class like in ChatControl
    {
        FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, username);
        return false;
    }
    else if (nullptr == userStatusToCompare)
    {
        return false;
    }

    if (!UserStatus::activeStatus.compare(*userStatusToCompare)) //0 when succes
    {
        return true;
    }

    _log.info("ChatRequest::isUserActive ERROR: User is bussy");
    printw("User is bussy. Try again later.");
    refresh();

    return false;
}

bool ChatRequest::approveChatInvitation() const
{
    _log.function("ChatRequest::approveChatInvitation() started");
    std::string decision;
    decision = ConsoleWindow::getStringFromConsoleWindow();

    std::transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
    if ("y" == decision || "yes" == decision)
    {
        _log.info("ChatRequest::approveChatInvitation Invitation accepted");
        return true;
    }
    else if ("n" == decision || "no" == decision)
    {
        _log.info("ChatRequest::approveChatInvitation() Invitation disaccepted");
        return false;
    }

    _log.info("ChatRequest::approveChatInvitation() Invitation disaccepted");
    return false;
}

std::string ChatRequest::sendAnswer(const std::string& senderUsername, AnswerType type) const
{
    _log.function("ChatRequest::sendAnswer() started");
    std::string folderNameWithoutNumber = senderUsername + "_" + LOCAL_USER;
    std::string folderFullName = *getChatFolderName(folderNameWithoutNumber);
    std::string flagPath = ENVIRONMENT_PATH::TO_FOLDER::CHATS + folderFullName;

    if (AnswerType::disaccepted == type)
    {
        FileInterface::Managment::createFile(flagPath + "/DISACCEPTED");
    }
    else if (AnswerType::accepted == type)
    {
        _log.function("ChatRequest::sendAnswer() Invitation accepted");
        FileInterface::Managment::createFile(flagPath + "/ACCEPTED");
        std::string chatFilename = folderNameWithoutNumber;
        return flagPath + "/" + chatFilename;
    }
    _log.function("ChatRequest::sendAnswer() Invitation dissaccepted");
    return "";
}

std::string ChatRequest::sendChatRequest(const std::string& receiverUsername) const
{
    _log.function("ChatRequest::sendChatRequest() started");
    changeUserStatus(LOCAL_USER, UserStatus::bussyStatus);
    //^ przez ta linijke są zakomentowane UT

    if (!isUserActive(receiverUsername))
    {
        return {};
    }

    ChatFabric chatFabric;
    std::string chatFileWithPath = chatFabric.createChatStructure(LOCAL_USER, receiverUsername);
    changeUserStatus(receiverUsername, UserStatus::bussyStatus);
    std::string invitationName = receiverUsername + "_" + LOCAL_USER;
    FileInterface::Managment::createFile(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS + invitationName);

    bool receiverDecision = waitForAnswer(receiverUsername);
    if(receiverDecision)
    {
        return chatFileWithPath;
    }

    auto chatFileFolder = *FileInterface::Accesor::getFolderName(chatFileWithPath);
    FileInterface::Managment::removeFile(chatFileFolder);
    changeUserStatus(LOCAL_USER, UserStatus::activeStatus);
    changeUserStatus(receiverUsername, UserStatus::activeStatus);
    return {};

}

void ChatRequest::showInvitation(const std::string& senderUsername) const
{
    _log.function("ChatRequest::showInvitation() started");
    clear();
    printw(("You get an invitation to chat form " + senderUsername + "\n").c_str());
    printw("Do you want to chat with this user (y/n)? \n");
    printw(">> ");
    refresh();
}

bool ChatRequest::waitForAnswer(const std::string& username) const
{
    _log.function("ChatRequest::waitForAnswer() started");
    std::string folderName = LOCAL_USER + "_" + username;
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

    _log.info("ChatRequest::waitForAnswer ERROR: User has not accepted the invitation");
    printw("User has not accepted the invitation.");
    sleep(1);
    return false;
}
