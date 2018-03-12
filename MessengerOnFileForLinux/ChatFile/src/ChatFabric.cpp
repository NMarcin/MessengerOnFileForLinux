#include <vector>
#include <stdlib.h>

#include <ChatFabric.hpp>

bool ChatFabric::createChatStructure(std::string usernameInviter, std::string usernameGuess)
{
    std::string chatFolderName = createChatFolder("a", "b");
    if("" == chatFolderName)
    {
        if(createChatFile("0a_b", "a", "b"))
        {
            return true;
        }
    }
    return false;
}


std::string ChatFabric::createChatFolder(std::string usernameInviter, std::string usernameGuess)
{
    int folderNumber = getFreeFolderNumber("/home/messenger/chats/");        // podmienic na zmienna srodowiskowa
    std::string newFolderName = std::to_string(folderNumber) + usernameInviter + "_" + usernameGuess;
    std::string systemCommand = "mkdir /home/messenger/chats/" + newFolderName; // jw
    bool commandStatus = system(systemCommand.c_str());

    if(commandStatus)
    {
        return newFolderName;
    }
    return {};
}

bool ChatFabric::createChatFile(std::string chatFolderName, std::string usernameInviter, std::string usernameGuess)
{
    std::string newFileName = usernameInviter + "_" + usernameGuess;
    std::string systemCommand = "touch /home/messenger/chats/" + chatFolderName + newFileName; // jw
    bool commandStatus = system(systemCommand.c_str());
    
    return commandStatus;
}

int ChatFabric::getFreeFolderNumber(std::string folderPath)
{
    int freeFolderNumber = -1;
    std::vector<std::string> filesInPath= {}; // pobranie wektora nazw plików w danym folderze alfabetycznie (to powinno potem być w interfejsie plikow)
    auto fileIterator = filesInPath.begin();

    for(int folderNumber = 0; 0 <= freeFolderNumber; ++folderNumber)    // aktualna funkcjonalnosc dziala tylko dla 10 rozmow jednoczesnie, TODO mnurzyns dla wiekszej ilosci
    {
        int fileNumber = atoi((*fileIterator).c_str());
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
    return freeFolderNumber;
}
