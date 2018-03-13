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

    return false; //TODO mwozniak co jest wprawdzi inna odpwiedz
    // poki co powoduje odrzucenie
}

bool ChatRequest::answerForChatRequest(const int usernamePid) const
{
    std::unique_ptr<std::string> senderUsername = getUsernameByProcessId(usernamePid);

    showInvitation(*senderUsername);
    bool decision = makeDecision();

    if (true == decision)
    {
        //createChatFile() //TODO mwozniak createchatfile od mnurzyn
        return true;
    }

    FileFlag::setFileFlag(FileFlagType::refuseChatInvitation, ""); //TODO mwozniak sciezka do pliku, ogarnac odmowe na syngale
    return false;
}

bool ChatRequest::changeUserStatus(const User& user, const std::string& newStatus) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::returnFileContent(loggedFile);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< const std::string> usernameToComapre = FileInterface::getRowField(x, usernameFieldInLoggedFile);
        std::string username = user.getUsername();

        if (!username.compare(*usernameToComapre)) //0 when succes
        {
            std::string updatedRow = *FileInterface::updateRowField(x, newStatus, statusFieldInLoggedFile);
            FileInterface::updateRow(loggedFile, updatedRow, username);

            return true;
        }
    }

    return false;
}

std::unique_ptr<std::string> ChatRequest::getUsernameByProcessId(const int userPid) const
{
    std::unique_ptr<std::vector<std::string>> loggedFileContent = FileInterface::returnFileContent(loggedFile);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< std::string> pidToComapre = FileInterface::getRowField(x, pidFieldInLoggedFile);
        int pid = std::atoi(pidToComapre->c_str());

        if (userPid == pid)
        {
            std::unique_ptr<std::string> username = FileInterface::getRowField(x, usernameFieldInLoggedFile);
            return username;
        }
    }

    return nullptr; //error
}


bool ChatRequest::isUserActive(const User& user) const
{
    std::unique_ptr<std::vector<std::string>>loggedFileContent = FileInterface::returnFileContent(loggedFile);

    for (auto &x : *loggedFileContent)
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

    int pid = receiver.getUserProcessIdFromSystem();
    sendSigusr1Signal(pid);

    for (int i = 0; i < timeToWaitForAnswer; i++)
    {
        if (FileInterface::isFileExists("chat.txt")) //TODO mwozniak chatfile name
        {
            std::cout <<"Udalo sie nawiazac kontakt. Możesz teraz chatowac z " + username << std::endl;
            return true;
        }
        else if (FileFlag::isFlagExist(FileFlagType::refuseChatInvitation, "")) //TODO mwonziak sciezka do pliku
        {
            std::cout <<"Nie nawiazano kontaktu z " + username << std::endl;
            FileFlag::removeFileFlag(FileFlagType::refuseChatInvitation, ""); //TODO mwonziak sciezka do pliku
            return false;
        }

        sleep(1);
    }

    std::cout << "Uzytkownik nie zaakcpetowal zaprosznia" << std::endl;

    changeUserStatus(LocalUser::getLocalUser().getUsername(), userActiveStatus);
    changeUserStatus(receiver.getUsername(), userActiveStatus);

    return false;
}

void ChatRequest::sendSigusr1Signal(const int userPid) const
{
    kill(userPid, SIGUSR1);
}


