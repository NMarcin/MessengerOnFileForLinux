#include <iostream>
#include <signal.h>
#include <algorithm>

#include <ChatRequest.hpp>
#include <User.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <ChatFabric.hpp>

ChatRequest::ChatRequest()
{
    log.info("ChatRequest C-TOR");
}

ChatRequest::~ChatRequest()
{
    log.info("ChatRequest D-TOR");
}

std::string ChatRequest::answerForChatRequest(const int usernamePid) const  // TODO mwozniak string przez sygnal lub gdzies jakos pobierany tutaj
{
    log.info("ChatRequest::answerForChatRequest started");
    std::unique_ptr<std::string> senderUsername = std::make_unique<std::string>(*getUsernameThroughPid(usernamePid));

    showInvitation(*senderUsername);
    bool decision = respondOnInvitation();

    if (decision)
    {
        sendAnswer(*senderUsername, AnswerType::accepted);
        return "true";  // TODO mwozniak: sciezka szybko ogarnac, bo testy jebna
    }

    sendAnswer(*senderUsername, AnswerType::disaccepted);
    return "false";
}

bool ChatRequest::changeUserStatus(const User& user, const std::string& newStatus) const
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
    std::string command= "ls " + static_cast<std::string>(ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER) + " | grep " + folderName;

    std::unique_ptr<std::string> folderFullName = std::make_unique<std::string>(ConsolControl::getStdoutFromCommand(command));

     if (!folderFullName->empty())
     {
         folderFullName->pop_back(); //usuwanie znaku konca lini
         return folderFullName ;
     }

     return nullptr;
}

std::unique_ptr<std::string> ChatRequest::getUsernameThroughPid(const int userPid) const
{
    log.info("ChatRequest::getUsernameThroughPid started");
    std::unique_ptr<std::vector<std::string>> loggedFileContent = FileInterface::Accesor::getFileContent(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< std::string> pidToComapre = FileInterface::Accesor::getRowField(x, FileStructure::FileField::pidFieldInLoggedFile);
        int pid = std::atoi(pidToComapre->c_str());

        if (0 == pid)
        {
            log.info("ChatRequest::getUsernameThroughPid ERROR: atoi failed");
            return nullptr; //error nie skonwertowalo
        }
        if (userPid == pid)
        {
            std::unique_ptr<std::string> username = FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile);
            return username;
        }
    }

    log.info("ChatRequest::getUsernameThroughPid ERROR: User does not exist");
    return nullptr; //error
}


std::unique_ptr<std::string> ChatRequest::getUserStatus(const std::string& username) const
{
    log.info("ChatRequest::getUserStatus started");
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::Accesor::getFileContent(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile);
        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::unique_ptr<std::string> userStatusToCompare = FileInterface::Accesor::getRowField(x, FileStructure::FileField::statusFieldInLoggedFile);
            return userStatusToCompare;
        }
    }

    log.info("ChatRequest::getUserStatus ERROR: User is offline or does not exist");
    std::cerr << "User is offline or does not exist" << std::endl;
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
    std::cerr << "User is bussy" << std::endl;
    return false;
}

bool ChatRequest::respondOnInvitation() const
{
    log.info("ChatRequest::respondOnInvitation started");
    std::string decision;
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
    return false; //TODO mwozniak co jesli wprawdzi inna odpwiedz
    // poki co powoduje odrzucenie
}

std::string ChatRequest::sendAnswer(const std::string& senderUsername, AnswerType type) const
{
    log.info("ChatRequest::sendAnswer started");
    std::string partOfFolderName = senderUsername + "_" + LocalUser::getLocalUser().getUsername();
    std::string folderFullName = *getChatFolderName(partOfFolderName);
    std::string flagPath = ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER + folderFullName;

    if (AnswerType::disaccepted == type)
    {
        FileInterface::Managment::createFile(flagPath + "/DISACCEPTED");
        return flagPath + "/" + partOfFolderName;
    }
    else if (AnswerType::accepted == type)
    {
        FileInterface::Managment::createFile(flagPath + "/ACCEPTED");
    }
    return "";
}

std::string ChatRequest::sendChatRequest(const std::string& username) const
{
    log.info("ChatRequest::sendChatRequest started");
    User receiver(username);

    //changeUserStatus(LocalUser::getLocalUser().getUsername(), FileField::FieldValue::userBussyStatus);
    //to ma byc tutaj, dla testow zakomentowane

    ChatFabric newChat;
    std::string chatFileWithPath = newChat.createChatStructure(LocalUser::getLocalUser().getUsername(), receiver.getUsername());

    if (!isUserActive(receiver.getUsername()))
    {
        return {};
    }
    changeUserStatus(receiver.getUsername(), FileStructure::FieldValue::userBussyStatus);
    int pid = receiver.getUserPid();
    if (0 == pid)
    {
        return {};
    }

    sendSigusr1Signal(pid);

    if (!waitForAnswer(receiver.getUsername()))
    {
        //TODO mwozniak usuwanie folderu rozmowy
        changeUserStatus(LocalUser::getLocalUser().getUsername(), FileStructure::FieldValue::userActiveStatus);
        changeUserStatus(receiver.getUsername(), FileStructure::FieldValue::userActiveStatus);
        return {};
    }

    return chatFileWithPath;
}

void ChatRequest::sendSigusr1Signal(const int userPid) const
{
    log.info("ChatRequest::sendSigusr1Signal started");
    kill(userPid, SIGUSR1);
}

void ChatRequest::showInvitation(const std::string& senderUsername) const
{
    log.info("ChatRequest::showInvitation started");
    std::cout << "You get an invitation to chat form " + senderUsername << std::endl;
    std::cout << "Do you want to chat with this user (y/n)? " << std::endl;
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
