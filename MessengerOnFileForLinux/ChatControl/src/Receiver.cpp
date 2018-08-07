#include <Receiver.hpp>

#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

Reciver::Reciver()
{
    //NOOP
}

Reciver::~Reciver()
{
    //NOOP
}

bool Reciver::readMessages()
{
// BLOKUJEMY DOSTĘP DO FOLDERU

    std::unique_ptr<std::vector<std::string>> messagesFileContent = FileInterface::Accesor::getFileContent(chatFileWithPath);
    auto fileContentIterator = messagesFileContent->end();
    while(fileContentIterator != messagesFileContent->begin()) // dany wiersz jest do odbiorcy oraz został już przeczytany wcześniej
    {
        --fileContentIterator;
        int messageFlag;
        messageFlag = std::atoi((FileInterface::Accesor::getRowField(*fileContentIterator, FileStructure::LoggedFile::username))->c_str()); // LoggedFile::username podmienic na odpowiedni stworzony przez mnowznia
        if( mineMessageUserFlag != messageFlag)
        {
            std::string purgeMessage;
            purgeMessage = purgeMessageFromRaw(*fileContentIterator);
            purgeMessagesStack.push(purgeMessage);
        }
        if( 0 == messageFlag)
        {
            std::string senderUsername;
            senderUsername = *FileInterface::Accesor::getRowField(*fileContentIterator, FileStructure::LoggedFile::username); // LoggedFile::username podmienic na odpowiedni stworzony przez mnowznia
            if( LocalUser::getLocalUser().getUsername() == senderUsername)
            {
                break;
            }
        }
    }
    //updateFlagsInFile()

// ODBLOKOWUJEMY DOSTĘP DO FOLDERU

    return false;
}

bool Reciver::getRawMessagesFromFile(std::string chatFileWithPath)
{
    return false;
}

std::string Reciver::getMessageFromStack()
{
    return "false";
}

std::string Reciver::purgeMessageFromRaw(std::string rawMessage)
{
    return "false";
}

bool Reciver::addMessageToQueue(std::queue<std::string> messagesToShowOnScreen, std::string purgeMessage)
{
    return false;
}
