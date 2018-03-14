#include <iostream>
#include <signal.h>

#include <ChatRequest.hpp>
#include <User.hpp>
#include <FileHandling.hpp>
#include <FileGuardian.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

ChatRequest::ChatRequest()
{
    //NOOP
}

ChatRequest::~ChatRequest()
{
    //NOOP
}

void ChatRequest::showInvitation(const std::string& senderUsername) const
{
    std::cout << "You get an invitation to chat form " + senderUsername << std::endl;
    std::cout << "Do you want to chat with this user (yes/no)? " << std::endl;
}

bool ChatRequest::makeDecision() const
{
    std::string decision;
    std::cin >> decision;
    if ("yes" == decision)
    {
        return true;
    }
    else if ("no" == decision)
    {
        return false;
    }

    return false; //TODO mwozniak co jesli wprawdzi inna odpwiedz
    // poki co powoduje odrzucenie
}

bool ChatRequest::sendAnswer(const std::string& senderUsername, FileFlagType type) const
{
    std::string flagName = senderUsername + "_" + LocalUser::getLocalUser().getUsername();

    if (FileFlagType::refuseChatInvitation == type)
    {
        FileFlag::setFileFlag(FileFlagType::refuseChatInvitation, CHATS_PATH, flagName); //TODO mwozniakogarnac odmowe na syngale
    }
    else if (FileFlagType::acceptChatInvitation == type)
    {
        FileFlag::setFileFlag(FileFlagType::acceptChatInvitation, CHATS_PATH, flagName);
    }
    return false;
}

bool ChatRequest::answerForChatRequest(const int usernamePid) const
{
    std::unique_ptr<std::string> senderUsername = std::make_unique<std::string>(*getUsernameByProcessId(usernamePid));

    showInvitation(*senderUsername);
    bool decision = makeDecision();

    if (true == decision)
    {
        sendAnswer(*senderUsername, FileFlagType::acceptChatInvitation);
        return true;
    }
    return sendAnswer(*senderUsername, FileFlagType::refuseChatInvitation);
}

bool ChatRequest::changeUserStatus(const User& user, const std::string& newStatus) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::getFileContent(LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::getRowField(x, usernameFieldInLoggedFile));
        std::string username = user.getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::string newRow = *FileInterface::updateRowField(x, newStatus, statusFieldInLoggedFile);
            FileInterface::updateRow(LOGGED_FILE, newRow, username);

            return true;
        }
    }

    return false;
}

std::unique_ptr<std::string> ChatRequest::getUsernameByProcessId(const int userPid) const
{
    std::unique_ptr<std::vector<std::string>> loggedFileContent = FileInterface::getFileContent(LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< std::string> pidToComapre = FileInterface::getRowField(x, pidFieldInLoggedFile);
        int pid = std::atoi(pidToComapre->c_str());

        if (0 == pid)
        {
            return nullptr; //error nie skonwertowalo
        }
        if (userPid == pid)
        {
            std::unique_ptr<std::string> username = FileInterface::getRowField(x, usernameFieldInLoggedFile);
            return username;
        }
    }

    return nullptr; //error
}


bool ChatRequest::isUserLogged(const std::string& username) const
{

}

bool ChatRequest::isUserActive(const User& user) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::getFileContent(LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = FileInterface::getRowField(x, usernameFieldInLoggedFile);

        if (!user.getUsername().compare(*usernameToComapre)) //0 when succes
        {
            std::unique_ptr<std::string> userStatusToCompare = FileInterface::getRowField(x, statusFieldInLoggedFile);

            if (!userActiveStatus.compare(*userStatusToCompare)) //0 when succes
            {
                return true;
            }

            std::cerr << "User is bussy" << std::endl;
            return false;
        }
    }

    std::cerr << "User is offline or does not exist" << std::endl;
    return false;
}

bool ChatRequest::sendChatRequest(const std::string& username) const
{
    User receiver(username);

    //changeUserStatus(LocalUser::getLocalUser().getUsername(), userBussyStatus);
    //to ma byc tutaj, dla testow zakomentowane

    if (!isUserActive(receiver.getUsername()))
    {
        return false;
    }

    changeUserStatus(receiver.getUsername(), userBussyStatus);

    int pid = receiver.getUserPid();
    sendSigusr1Signal(pid);


    if (!waitForAnswer(receiver.getUsername()))
    {
        changeUserStatus(LocalUser::getLocalUser().getUsername(), userActiveStatus);
        changeUserStatus(receiver.getUsername(), userActiveStatus);
        return false;
    }

    //createChatFile(); TODO mwozniak
    return true;
}

bool ChatRequest::waitForAnswer(const std::string& username) const
{
    std::string flagName = LocalUser::getLocalUser().getUsername() + "_" + username;

    for (int i = 0; i < timeToWaitForAnswer; i++)
    {

        if (FileFlag::isFlagExist(FileFlagType::acceptChatInvitation, CHATS_PATH, flagName))
        {
            std::cout << username + " has accepted the invitation. You can start chat" << std::endl;
            FileFlag::removeFileFlag(FileFlagType::acceptChatInvitation, CHATS_PATH, flagName);
            return true;
        }
        else if (FileFlag::isFlagExist(FileFlagType::refuseChatInvitation, CHATS_PATH, flagName))
        {
            std::cout << "User has not accepted the invitation" << std::endl;
            FileFlag::removeFileFlag(FileFlagType::refuseChatInvitation, CHATS_PATH, flagName);
            return false;
        }

        sleep(1);
    }

    std::cout << "User has not accepted the invitation" << std::endl;
    return false;
}

void ChatRequest::sendSigusr1Signal(const int userPid) const
{
    kill(userPid, SIGUSR1);
}


