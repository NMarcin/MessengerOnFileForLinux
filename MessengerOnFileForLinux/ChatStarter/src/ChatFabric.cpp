#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include <ChatFabric.hpp>
#include <GlobalVariables.hpp>
#include <FileHandling.hpp>

ChatFabric::ChatFabric()
{
    log.info("ChatFabric C-TOR");
}

ChatFabric::~ChatFabric()
{
    log.info("ChatFabric D-TOR");
}

std::string ChatFabric::createChatStructure(const std::string& usernameInviter, const std::string& usernameGuess) const
{
    log.info("ChatFabric::createChatStructure started");
    std::string chatFolderName = createChatFolder(usernameInviter, usernameGuess);
    if(!chatFolderName.empty())
    {
        std::string chatFileWithPath = createChatFile(chatFolderName, usernameInviter, usernameGuess);
        if(!chatFileWithPath.empty())
        {
            log.info(("ChatFabric::createChatStructure succes, chatFileWithPath:" + chatFileWithPath).c_str());
            return chatFileWithPath;
        }
        log.info("ChatFabric::createChatStructure ERROR: createChatFile failed.");
        return {};
   }
    log.info("ChatFabric::createChatStructure ERROR: createChatFolder failed");
    return {};
}

std::string ChatFabric::createChatFolder(const std::string& usernameInviter, const std::string& usernameGuess) const
{
    int folderNumber = getFreeFolderNumber();
    std::string newFolderName = ENVIRONMENT_PATH::TO_FOLDER::CHATS + std::to_string(folderNumber) + usernameInviter + "_" + usernameGuess + "/";
    std::string systemCommand = "mkdir " + newFolderName;
    std::string systemCommand2 = "chmod 700 " + newFolderName;
    bool commandStatus = system(systemCommand.c_str());
    system(systemCommand2.c_str());
    systemCommand = "setfacl -m u:" + usernameGuess + ":rwx " + newFolderName;
    system(systemCommand.c_str());
    //TODO mawoznia jest ok, ale jeszcze nie trzeba ogarnac mzliwos usuwania

    if(!commandStatus)
    {
        log.info(("ChatFabric::createChatFolder succes, folderName: " + newFolderName).c_str());
        return newFolderName;
    }
    log.info("ChatFabric::createChatFolder commandStatus failure");
    return {};
}

std::string ChatFabric::createChatFile(const std::string& chatFolderName, const std::string& usernameInviter, const std::string& usernameGuess) const
{
    std::string newChatFileWithPath = chatFolderName + usernameInviter + "_" + usernameGuess;
    bool folderCreating = FileInterface::Managment::createFile(newChatFileWithPath);

    if(!folderCreating)
    {
        log.info("ChatFabric::createChatFile folderCreating done");
        return newChatFileWithPath;
    }
    log.info("ChatFabric::createChatFile folderCreating failure");
    return {};
}

std::vector<int> ChatFabric::getBusyNumbers() const
{
    std::vector<std::string> filesInPath = *FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::CHATS); // daje mi wektor
    std::vector<int> busyNumbers;

    for(auto fileName : filesInPath)
    {
        busyNumbers.push_back(std::atoi(fileName.c_str()));
    }
    std::sort(busyNumbers.begin(), busyNumbers.end(), std::less<int>());
    return busyNumbers;
}

int ChatFabric::findMissingNumber(std::vector<int>& busyNumbers_) const
{
    std::vector<int> busyNumbers = busyNumbers_;
    std::sort(busyNumbers.begin(), busyNumbers.end());

    int numberIteration = 0;
    for(auto number : busyNumbers)
    {
        if(numberIteration != number)
        {
            return numberIteration;
        }
        ++numberIteration;
    }
    return -1;
}

int ChatFabric::getFreeFolderNumber() const
{
    std::vector<int> busyNumbers = getBusyNumbers();
    if(busyNumbers.empty())
    {
        return 0;
    }
    else if(busyNumbers.back()+1 == busyNumbers.size())
    {
        return busyNumbers.back()+1;
    }
    else
    {
        return findMissingNumber(busyNumbers);
    }
}
