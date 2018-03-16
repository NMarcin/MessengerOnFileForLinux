#include <iostream>
#include <signal.h>

#include <ChatRequest.hpp>
#include <User.hpp>
#include <FileHandling.hpp>
#include <FileGuardian.hpp>
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
    bool decision = makeDecision();

    if (true == decision)
    {
        sendAnswer(*senderUsername, AnswerType::accepted);
        return true;
    }
    return sendAnswer(*senderUsername, AnswerType::disapproved);
}

bool ChatRequest::changeUserStatus(const User& user, const std::string& newStatus) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::getFileContent(FILE_::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = std::make_unique<std::string>(*FileInterface::getRowField(x, FileField::usernameFieldInLoggedFile));
        std::string username = user.getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::string changedRow = *FileInterface::updateRowField(x, newStatus, FileField::statusFieldInLoggedFile);
            FileInterface::updateRow(FILE_::LOGGED_FILE, changedRow, username);

            return true;
        }
    }

    return false;
}

std::unique_ptr<std::string> ChatRequest::getUsernameThroughPid(const int userPid) const
{
    std::unique_ptr<std::vector<std::string>> loggedFileContent = FileInterface::getFileContent(FILE_::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< std::string> pidToComapre = FileInterface::getRowField(x, FileField::pidFieldInLoggedFile);
        int pid = std::atoi(pidToComapre->c_str());

        if (0 == pid)
        {
            return nullptr; //error nie skonwertowalo
        }
        if (userPid == pid)
        {
            std::unique_ptr<std::string> username = FileInterface::getRowField(x, FileField::usernameFieldInLoggedFile);
            return username;
        }
    }

    return nullptr; //error
}


std::unique_ptr<std::string> ChatRequest::getUserStatus(const std::string& username) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::getFileContent(FILE_::LOGGED_FILE);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr<std::string> usernameToComapre = FileInterface::getRowField(x, FileField::usernameFieldInLoggedFile);
        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::unique_ptr<std::string> userStatusToCompare = FileInterface::getRowField(x, FileField::statusFieldInLoggedFile);
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

    if (!FileField::FieldValue::userActiveStatus.compare(*userStatusToCompare)) //0 when succes
    {
        return true;
    }

    std::cerr << "User is bussy" << std::endl;
    return false;

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

bool ChatRequest::sendAnswer(const std::string& senderUsername, AnswerType type) const
{
    std::string flagName = senderUsername + "_" + LocalUser::getLocalUser().getUsername();

    if (AnswerType::disapproved == type)
    {
        FileInterface::createFile(flagName + "_DISAPRPROVED", FILE_::PATH::CHATS_PATH);
    }
    else if (AnswerType::accepted == type)
    {
        FileInterface::createFile(flagName + "_ACCEPTED", FILE_::PATH::CHATS_PATH);
    }
    return false;
}

bool ChatRequest::sendChatRequest(const std::string& username) const
{
    User receiver(username);

    //changeUserStatus(LocalUser::getLocalUser().getUsername(), FileField::FieldValue::userBussyStatus);
    //to ma byc tutaj, dla testow zakomentowane

    if (!isUserActive(receiver.getUsername()))
    {
        return false;
    }

    changeUserStatus(receiver.getUsername(), FileField::FieldValue::userBussyStatus);

    int pid = receiver.getUserPid();
    if (0 == pid)
    {
        return false;
    }

    sendSigusr1Signal(pid);

    if (!waitForAnswer(receiver.getUsername()))
    {
        changeUserStatus(LocalUser::getLocalUser().getUsername(), FileField::FieldValue::userActiveStatus);
        changeUserStatus(receiver.getUsername(), FileField::FieldValue::userActiveStatus);
        return false;
    }

    ChatFabric newChat;
    newChat.createChatStructure(LocalUser::getLocalUser().getUsername(), receiver.getUsername());

    return true;
}

void ChatRequest::sendSigusr1Signal(const int userPid) const
{
    kill(userPid, SIGUSR1);
}

void ChatRequest::showInvitation(const std::string& senderUsername) const
{
    std::cout << "You get an invitation to chat form " + senderUsername << std::endl;
    std::cout << "Do you want to chat with this user (yes/no)? " << std::endl;
}

bool ChatRequest::waitForAnswer(const std::string& username) const
{
    std::string flagName = LocalUser::getLocalUser().getUsername() + "_" + username;
    static constexpr int timeToWaitForAnswer = 20;

    for (int i = 0; i < timeToWaitForAnswer; i++)
    {
        if (FileInterface::isFileExists(flagName + "_ACCEPTED", FILE_::PATH::CHATS_PATH))
        {
            std::cout << username + " has accepted the invitation. You can start chat" << std::endl;
            FileInterface::removeFile(flagName + "_ACCEPTED", FILE_::PATH::CHATS_PATH);
            return true;
        }
        else if (FileInterface::isFileExists(flagName + "_DISAPRPROVED", FILE_::PATH::CHATS_PATH))
        {
            std::cout << "User has not accepted the invitation" << std::endl;
            FileInterface::removeFile(flagName + "_DISAPRPROVED", FILE_::PATH::CHATS_PATH);
            return false;
        }

        sleep(1);
    }

    std::cout << "User has not accepted the invitation" << std::endl;
    return false;
}
