#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include <ChatFabric.hpp>
#include <GlobalVariables.hpp>
#include <FileHandling.hpp>



std::string ChatFabric::createChatStructure(const std::string& usernameInviter, const std::string& usernameGuess) const
{
    _log.function("ChatFabric::createChatStructure() started");
    std::string chatFolderName = createChatFolder(usernameInviter, usernameGuess);
    if(!chatFolderName.empty())
    {
        std::string chatFileWithPath = createChatFile(chatFolderName, usernameInviter, usernameGuess);
        if(!chatFileWithPath.empty())
        {
            _log.info(("ChatFabric::createChatStructure succes, chatFileWithPath:" + chatFileWithPath).c_str());
            return chatFileWithPath;
        }
        _log.info("ChatFabric::createChatStructure ERROR: createChatFile failed.");
        return {};
   }
    _log.info("ChatFabric::createChatStructure ERROR: createChatFolder failed");
    return {};
}

std::string ChatFabric::createChatFolder(const std::string& usernameInviter, const std::string& usernameGuess) const
{
    _log.function("ChatFabric::createChatFolder() started");
    int folderNumber = getFreeFolderNumber();
    std::string newFolderName = ENVIRONMENT_PATH::TO_FOLDER::CHATS + std::to_string(folderNumber) + usernameInviter + "_" + usernameGuess + "/";
    std::string systemCommand = "mkdir " + newFolderName;
    std::string systemCommand2 = "chmod 700 " + newFolderName;
    bool commandStatus = system(systemCommand.c_str());
    system(systemCommand2.c_str());
    systemCommand = "setfacl -m u:" + usernameGuess + ":rwx " + newFolderName;
    system(systemCommand.c_str());

    if(!commandStatus)
    {
        _log.info(("ChatFabric::createChatFolder succes, folderName: " + newFolderName).c_str());
        return newFolderName;
    }
    _log.info("ChatFabric::createChatFolder commandStatus failure");
    return {};
}

std::string ChatFabric::createChatFile(const std::string& chatFolderName, const std::string& usernameInviter, const std::string& usernameGuess) const
{
    _log.function("ChatFabric::createChatFile() started");
    std::string newChatFileWithPath = chatFolderName + usernameInviter + "_" + usernameGuess;
    bool folderCreating = FileInterface::Managment::createFile(newChatFileWithPath);

    if(folderCreating)
    {
        _log.info("ChatFabric::createChatFile folderCreating done");
        return newChatFileWithPath;
    }
    _log.info("ChatFabric::createChatFile folderCreating failure");
    return {};
}

std::vector<int> ChatFabric::getBusyNumbers() const
{
    _log.function("ChatFabric::getBusyNumbers() started");
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
    _log.function("ChatFabric::findMissingNumber() started");
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
    _log.function("ChatFabric::getFreeFolderNumber() started");
    std::vector<int> busyNumbers = getBusyNumbers();
    if(busyNumbers.empty())
    {
        return 0;
    }
    else if(busyNumbers.back() + 1u  == busyNumbers.size())
    {
        return busyNumbers.back() + 1;
    }
    else
    {
        return findMissingNumber(busyNumbers);
    }
}
