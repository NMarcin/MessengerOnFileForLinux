#include <vector>
#include <stdlib.h>
#include <iostream>

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
    int folderNumber = getFreeFolderNumber(ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER);
    std::string newFolderName = ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER + std::to_string(folderNumber) + usernameInviter + "_" + usernameGuess + "/";
    std::string systemCommand = "mkdir " + newFolderName;
    std::string systemCommand2 = "chmod 777 " + newFolderName;
    bool commandStatus = system(systemCommand.c_str());
    system(systemCommand2.c_str());

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

int ChatFabric::getFreeFolderNumber(const std::string& folderPath) const
{
    int freeFolderNumber = -1;
    std::vector<std::string> filesInPath= *FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::CHATS_FOLDER); //TODO mnurzyns jakis move czy swap
    auto fileIterator = filesInPath.begin();

    if(filesInPath.empty())
    {
        freeFolderNumber = 0;
        return freeFolderNumber;
    }

    for(int folderNumber = 0; 0 <= freeFolderNumber; ++folderNumber)    // aktualna funkcjonalnosc dziala tylko dla 10 rozmow jednoczesnie, TODO mnurzyns dla wiekszej ilosci
    {
        int fileNumber = (*fileIterator)[0];                            // atoi((*fileIterator).c_str()); gdy zadziala na wiecej niz 10 rozmow
        if(fileNumber > folderNumber)
        {
            freeFolderNumber = folderNumber;
        }
        else if(filesInPath.end() == fileIterator)
        {
            freeFolderNumber = folderNumber + 1;
        }
        else
        {
            ++fileIterator;
        }
    }   // TODO mnurzyns -> ogarnac to funkcje i dodac logi
    //return 1;
    return 3;
}
