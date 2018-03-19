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
    //NOOP
}

ChatRequest::~ChatRequest()
{
    //NOOP
}

bool ChatRequest::answerForChatRequest(const int usernamePid) const
{
    std::unique_ptr<std::string> senderUsername = std::make_unique<std::string>(*getUsernameThroughPid(usernamePid));

    showInvitation(*senderUsername);
    bool decision = respondOnInvitation();

    if (decision)
    {
        sendAnswer(*senderUsername, AnswerType::accepted);
        return true;
    }

    return sendAnswer(*senderUsername, AnswerType::disaccepted);
}

bool ChatRequest::changeUserStatus(const User& user, const std::string& newStatus) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::Accesor::getFileContent(ENIVRONMENTAL_PATH::PATH_TO_FILE::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile));
        std::string username = user.getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::string changedRow = *FileInterface::Modification::updateRowField(x, newStatus, FileStructure::FileField::statusFieldInLoggedFile);
            FileInterface::Modification::updateRow(ENIVRONMENTAL_PATH::PATH_TO_FILE::LOGGED_FILE, changedRow, username);

            return true;
        }
    }

    return false;
}

std::unique_ptr<std::string> ChatRequest::getChatFolderName(const std::string& folderName) const
{
    std::string command= "ls " + static_cast<std::string>(ENIVRONMENTAL_PATH::PATH_TO_FOLDER::CHATS_FOLDER) + " | grep " + folderName;

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
    std::unique_ptr<std::vector<std::string>> loggedFileContent = FileInterface::Accesor::getFileContent(ENIVRONMENTAL_PATH::PATH_TO_FILE::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< std::string> pidToComapre = FileInterface::Accesor::getRowField(x, FileStructure::FileField::pidFieldInLoggedFile);
        int pid = std::atoi(pidToComapre->c_str());

        if (0 == pid)
        {
            return nullptr; //error nie skonwertowalo
        }
        if (userPid == pid)
        {
            std::unique_ptr<std::string> username = FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile);
            return username;
        }
    }

    return nullptr; //error
}


std::unique_ptr<std::string> ChatRequest::getUserStatus(const std::string& username) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::Accesor::getFileContent(ENIVRONMENTAL_PATH::PATH_TO_FILE::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = FileInterface::Accesor::getRowField(x, FileStructure::FileField::usernameFieldInLoggedFile);
        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::unique_ptr<std::string> userStatusToCompare = FileInterface::Accesor::getRowField(x, FileStructure::FileField::statusFieldInLoggedFile);
            return userStatusToCompare;
        }
    }

    std::cerr << "User is offline or does not exist" << std::endl;
    return nullptr;
}


bool ChatRequest::isUserActive(const User& user) const
{

    std::unique_ptr<std::string> userStatusToCompare = getUserStatus(user.getUsername());

    if (nullptr == userStatusToCompare)
    {
        return false;
    }

    if (!FileStructure::FieldValue::userActiveStatus.compare(*userStatusToCompare)) //0 when succes
    {
        return true;
    }

    std::cerr << "User is bussy" << std::endl;
    return false;

}

bool ChatRequest::respondOnInvitation() const
{
    std::string decision;
    std::cin >> decision;
    std::transform(decision.begin(), decision.end(), decision.begin(), ::tolower);

    if ("y" == decision || "yes" == decision)
    {
        return true;
    }
    else if ("n" == decision || "no" == decision)
    {
        return false;
    }

    return false; //TODO mwozniak co jesli wprawdzi inna odpwiedz
    // poki co powoduje odrzucenie
}

bool ChatRequest::sendAnswer(const std::string& senderUsername, AnswerType type) const
{
    std::string partOfFolderName = senderUsername + "_" + LocalUser::getLocalUser().getUsername();
    std::string folderFullName = *getChatFolderName(partOfFolderName);
    std::string flagPath = ENIVRONMENTAL_PATH::PATH_TO_FOLDER::CHATS_FOLDER + folderFullName;

    if (AnswerType::disaccepted == type)
    {
        FileInterface::Managment::createFile(flagPath + "/DISACCEPTED");
    }
    else if (AnswerType::accepted == type)
    {
        FileInterface::Managment::createFile(flagPath + "/ACCEPTED");
    }
    return false;
}

bool ChatRequest::sendChatRequest(const std::string& username) const
{

    User receiver(username);

    //changeUserStatus(LocalUser::getLocalUser().getUsername(), FileField::FieldValue::userBussyStatus);
    //to ma byc tutaj, dla testow zakomentowane

    ChatFabric newChat;
    newChat.createChatStructure(LocalUser::getLocalUser().getUsername(), receiver.getUsername());

    if (!isUserActive(receiver.getUsername()))
    {
        return false;
    }
    changeUserStatus(receiver.getUsername(), FileStructure::FieldValue::userBussyStatus);

    int pid = receiver.getUserPid();
    if (0 == pid)
    {
        return false;
    }

    sendSigusr1Signal(pid);

    if (!waitForAnswer(receiver.getUsername()))
    {
        //TODO mwozniak usuwanie folderu rozmowy
        changeUserStatus(LocalUser::getLocalUser().getUsername(), FileStructure::FieldValue::userActiveStatus);
        changeUserStatus(receiver.getUsername(), FileStructure::FieldValue::userActiveStatus);
        return false;
    }

    return true;
}

void ChatRequest::sendSigusr1Signal(const int userPid) const
{
    kill(userPid, SIGUSR1);
}

void ChatRequest::showInvitation(const std::string& senderUsername) const
{
    std::cout << "You get an invitation to chat form " + senderUsername << std::endl;
    std::cout << "Do you want to chat with this user (y/n)? " << std::endl;
}

bool ChatRequest::waitForAnswer(const std::string& username) const
{
    std::string folderName = LocalUser::getLocalUser().getUsername() + "_" + username;
    std::string folderFullName = *getChatFolderName(folderName);

    const int timeToWaitForAnswer = 20;
    const std::string flagPath = ENIVRONMENTAL_PATH::PATH_TO_FOLDER::CHATS_FOLDER + folderFullName;

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

    std::cout << "User has not accepted the invitation." << std::endl;
    return false;
}
