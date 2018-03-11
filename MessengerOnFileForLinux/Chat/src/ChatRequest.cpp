#include <ChatRequest.hpp>
#include <User.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

#include <iostream>
#include <signal.h>

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
    std::unique_ptr< std::string> senderUsername = getUsernameByProcessId(usernamePid);

    std::cout << "Dostales zaproszenie na chat od " + *senderUsername << std::endl;
    std::cout << "Czy chcesz z nim rozmowaiac (tak/nie)? " << std::endl;

    std::string decision;
    std::cin >> decision;

    if ("tak" == decision)
    {
        //createChatFile()
        createFile("chat.txt");
        std::cout << "Nawiazales kontakt z " + *senderUsername << std::endl;
        return true;
    }
    else if ("nie" == decision)
    {
        //tworze jakis plik, do przemyslenia. Albo flage ?
        createFile("NOchat.txt");
        //TODO ogarnac to na syngale
        return false;
    }
}

bool ChatRequest::changeUserStatus(const User & user, const std::string& newStatus) const
{
    std::unique_ptr< std::vector< std::string>>loggedFileContent = returnFileContent(loggedFile);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< const std::string> usernameToComapre = getRowField(x, usernameFieldInLoggedFile);

        if (!user.getUsername().compare(*usernameToComapre)) //0 when succes
        {
            std::string updatedRow = *updateRowField(x, newStatus, statusFieldInLoggedFile);
            updateRow(loggedFile, updatedRow, user.getUsername());

            return true;
        }
    }

    return false;
}

std::unique_ptr< std::string> ChatRequest::getUsernameByProcessId(const int userPid) const
{
    std::unique_ptr< std::vector< std::string>>loggedFileContent = returnFileContent(loggedFile);

    for (auto& x : *loggedFileContent)
    {
        std::unique_ptr< std::string> pidToComapre = getRowField(x, pidFieldInLoggedFile);
        int pid = std::atoi(pidToComapre->c_str());

        if (userPid == pid)
        {
            std::unique_ptr< std::string> username = getRowField(x, usernameFieldInLoggedFile);
            return username;
        }
    }

    return nullptr; //error
}


bool ChatRequest::isUserActive(const User & user) const
{
    std::unique_ptr< std::vector< std::string>>loggedFileContent = returnFileContent(loggedFile);

    for (auto &x : *loggedFileContent)
    {
        std::unique_ptr< const std::string> usernameToComapre = getRowField(x, usernameFieldInLoggedFile);

        if (!user.getUsername().compare(*usernameToComapre)) //0 when succes
        {
            std::unique_ptr< const std::string> userStatusToCompare = getRowField(x, statusFieldInLoggedFile);

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
        if (isFileExists("chat.txt"))
        {
            std::cout <<"Udalo sie nawiazac kontakt. Możesz teraz chatowac z " + username << std::endl;
            return true;
        }
        else if (isFileExists("NOchat.txt"))
        {
            std::cout <<"Nie nawiazano kontaktu z " + username << std::endl;
            removeFile("NOchat.txt");
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


