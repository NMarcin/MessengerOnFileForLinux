#include <vector>

#include <ChatFabric.hpp>

bool ChatFabric::createChatStructure(std::string usernameInviter, std::string usernameGuess)
{
    if(createChatFolder("a", "b"))
    {
        if(createChatFile("a", "b"))
        {
            return true;
        }
    }
    return false;
}


bool ChatFabric::createChatFolder(std::string usernameInviter, std::string usernameGuess)
{
    // tutaj potrzebuje cd do /home/messenger/chats/
    // sprawdzenie pierwszego wolnego numerka 0mnurzyn_mwoznia2
    // mkdir 0mnurzyns)mwoznia2
    return true;
}

bool ChatFabric::createChatFile(std::string usernameInviter, std::string usernameGuess)
{
    // tutaj potrzebny cd do /home/messenger/chats/odpowiedni_plik
    // touch usernameInviter_usernameGuess
    return true;
}

int ChatFabric::getFreeFolderNumber()
{
    int freeFolderNumber = -1;
    std::vector<std::string> filesInPath= {}; // pobranie wektora nazw plików w danym folderze alfabetycznie (to powinno potem być w interfejsie plikow)
    auto fileIterator = filesInPath.begin();

    for(int folderNumber = 0; 0 <= freeFolderNumber; ++folderNumber)
    {
        int fileNumber = (*fileIterator)[0];
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

int ChatFabric::getNumberFromName()
{
    return 0;
}
