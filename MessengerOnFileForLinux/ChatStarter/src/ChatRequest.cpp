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

std::string ChatRequest::answerForChatRequest(const std::string& senderUsername) const//(const int usernamePid) const  // TODO mwozniak string przez sygnal
{
    log.info("ChatRequest::answerForChatRequest started");
    std::string invitationName =  LocalUser::getLocalUser().getUsername() + "_" + senderUsername;
    FileInterface::Managment::removeFile(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS_FOLDER + invitationName);
    showInvitation(senderUsername);
    bool decision = respondOnInvitation();

    if (decision)
    {
        return sendAnswer(senderUsername, AnswerType::accepted);
    }

    return sendAnswer(senderUsername, AnswerType::disaccepted);
}

bool ChatRequest::changeUserStatus(const User& user, const std::string& newStatus) const    // TODO mnurzyns mwozniak po zmianie fora sprawdzic
{
    log.info("ChatRequest::changeUserStatus started");
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::Accesor::getFileContent(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile));
        std::string username = user.getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            FileInterface::Modification::updateRowField(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE, x, newStatus, FileStructure::FileField::statusFieldInLoggedFile);
            return true;
        }
    }

    return false;
}

std::unique_ptr<std::string> ChatRequest::getChatFolderName(const std::string& folderName) const
{
    log.info("ChatRequest::getChatFolderName started");
    std::string command= "ls " + ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER + " | grep " + folderName;
    std::unique_ptr<std::string> folderFullName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command));
    std::string logData = "ChatRequest::getChatFolderName -> " + *folderFullName;
    log.info(logData.c_str());
     if (!folderFullName->empty())
     {
         folderFullName->pop_back(); //usuwanie znaku konca lini
         return folderFullName ;
     }

     return nullptr;
}

std::unique_ptr<std::string> ChatRequest::getUserStatus(const std::string& username) const
{
    log.info("ChatRequest::getUserStatus started");
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::Accesor::getFileContent(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE);

    for (auto x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile);
        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::unique_ptr<std::string> userStatusToCompare = FileInterface::Accesor::getRowField(x, FileStructure::FileField::statusFieldInLoggedFile);
            return userStatusToCompare;
        }
    }

    log.info("ChatRequest::getUserStatus ERROR: User is offline or does not exist");
    printw("User is offline or does not exist.");
    refresh();
    //std::cerr << "User is offline or does not exist" << std::endl;
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

    if (!FileStructure::FieldValue::userActiveStatus.compare(*userStatusToCompare)) //0 when succes
    {
        return true;
    }

    log.info("ChatRequest::isUserActive ERROR: User is bussy");
    printw("User is bussy. Try again later.");
    refresh();
    //std::cerr << "User is bussy" << std::endl;
    return false;
}

bool ChatRequest::respondOnInvitation() const
{
    log.info("ChatRequest::respondOnInvitation started");
    std::string decision;
    //decision = Display::getStringFromMainWindow(); //TODO mwoznia PROBLEM Z UT
    std::cin >> decision;
    std::transform(decision.begin(), decision.end(), decision.begin(), ::tolower);  // TODO mwozniak check tolower on string

    if ("y" == decision || "yes" == decision)
    {
        log.info("ChatRequest::respondOnInvitation Invitation accepted");
        return true;
    }
    else if ("n" == decision || "no" == decision)
    {
        log.info("ChatRequest::respondOnInvitation Invitation disaccepted");
        return false;
    }

    log.info("ChatRequest::respondOnInvitation Invitation disaccepted");
    return false; //TODO mwozniak co jesli wprawdzi inna odpwiedz (może for na 5 iteracji)
}

std::string ChatRequest::sendAnswer(const std::string& senderUsername, AnswerType type) const
{
    log.info("ChatRequest::sendAnswer started");
    std::string folderNameWithoutNumber = senderUsername + "_" + LocalUser::getLocalUser().getUsername();
    std::string folderFullName = *getChatFolderName(folderNameWithoutNumber);
    std::string flagPath = ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER + folderFullName;

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
    //changeUserStatus(LocalUser::getLocalUser().getUsername(), FileStructure::FieldValue::userBussyStatus);
    //zakomentowane dla testow na jednym terminalu

    ChatFabric chatFabric;
    std::string chatFileWithPath = chatFabric.createChatStructure(LocalUser::getLocalUser().getUsername(), receiver.getUsername());

    if (!isUserActive(receiver.getUsername()))  // TODO mwozniak polaczyc z ChatFabric w ifie, usunac !, a else return {}
    {
        return {};
    }
    changeUserStatus(receiver.getUsername(), FileStructure::FieldValue::userBussyStatus);

    std::string invitationName = username + "_" + LocalUser::getLocalUser().getUsername();
    FileInterface::Managment::createFile(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS_FOLDER + invitationName);

    bool receiverDecision = waitForAnswer(receiver.getUsername());
    if(receiverDecision)
    {
        return chatFileWithPath;
    }
    //TODO mwozniak usuwanie folderu rozmowy
    changeUserStatus(LocalUser::getLocalUser().getUsername(), FileStructure::FieldValue::userActiveStatus);
    changeUserStatus(receiver.getUsername(), FileStructure::FieldValue::userActiveStatus);
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
    const std::string flagPath = ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER + folderFullName;

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
