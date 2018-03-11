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
    // pobranie wektora nazw plików w danym folderze alfabetycznie (to powinno potem być w interfejsie plikow)
    // iterator na pierwszy element
    for(int folderNumber = 0; 0 <= freeFolderNumber; ++folderNumber)
    {
        // pobranie pierwszej litery z nazwy na ktora wskazuje iterator
        if(true) // sprawdzenie czy ta liczba jest wieksza od folderNumber
        {
            freeFolderNumber = folderNumber;
        }
        else if(true) // iterator wskazuje na ostatni element
        {
            freeFolderNumber = folderNumber + 1;
        }
        else
        {
            // iterator++;
        }
    }
    return freeFolderNumber;
}
