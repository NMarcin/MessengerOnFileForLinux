#include <vector>
#include <stdlib.h>
#include <iostream>

#include <ChatFabric.hpp>
#include <FileHandling.hpp>

ChatFabric::ChatFabric()
{
    log.info("ChatFabric C-TOR");
}

ChatFabric::~ChatFabric()
{
    log.info("ChatFabric D-TOR");
}

bool ChatFabric::createChatStructure(const std::string& usernameInviter, const std::string& usernameGuess) const
{
    log.info("ChatFabric::createChatStructure started");
    std::string chatFolderName = createChatFolder(usernameInviter, usernameGuess);
    //if("" == chatFolderName)
    if (!chatFolderName.empty())
    {
        if(createChatFile(chatFolderName, usernameInviter, usernameGuess))
        {
            return true;
        }
        log.info("ChatFabric::createChatStructure ERROR: createChatFile failed.");
        return false;
   }
    log.info("ChatFabric::createChatStructure ERROR: createChatFolder failed");
    return false;
}

std::string ChatFabric::createChatFolder(const std::string& usernameInviter, const std::string& usernameGuess) const
{
    int folderNumber = getFreeFolderNumber("/home/messenger/chats/");        // podmienic na zmienna srodowiskowa
    std::string newFolderName = std::to_string(folderNumber) + usernameInviter + "_" + usernameGuess;
    std::string systemCommand = "mkdir /home/messenger/chats/" + newFolderName; // jw
    bool commandStatus = system(systemCommand.c_str());

    if(commandStatus)
    {
        log.info("ChatFabric::createChatFolder commandStatus = true");
        return newFolderName;
    }
    log.info("ChatFabric::createChatFolder commandStatus == false");
    return {};
}

bool ChatFabric::createChatFile(const std::string& chatFolderName, const std::string& usernameInviter, const std::string& usernameGuess) const
{
    std::cout << "tworze plik" ;
    std::string newFileName = usernameInviter + "_" + usernameGuess;
    std::string systemCommand = "touch /home/messenger/chats/" + chatFolderName + "/" + newFileName; // jw, TODO mwozniak zrobic w interfejcie plikow
    bool commandStatus = system(systemCommand.c_str());

    return commandStatus;
}

int ChatFabric::getFreeFolderNumber(const std::string& folderPath) const
{
    int freeFolderNumber = -1;
    std::vector<std::string> filesInPath= {}; // pobranie wektora nazw plików w danym folderze alfabetycznie (to powinno potem być w interfejsie plikow)
    auto fileIterator = filesInPath.begin();

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
    }
    //return freeFolderNumber;
    return 1;
}
