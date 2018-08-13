#include <Receiver.hpp>

#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>
#include <iostream>
#include <thread>
#include <chrono>

Receiver::Receiver(std::string chatFileWithPath, std::string mineMessageUserFlag)
                : chatFileWithPath_(chatFileWithPath)
                , mineMessageUserFlag_(mineMessageUserFlag)
{
    //NOOP
}

Receiver::~Receiver()
{
    //NOOP
}

bool Receiver::readMessagesToStack()
{
// BLOKUJEMY DOSTĘP DO FOLDERU TODO mwozniak
    auto isFileLock = false;
    auto folder = *FileInterface::Accesor::getFolderName(chatFileWithPath_);
    while (!isFileLock)
    {
        isFileLock = FileInterface::lockFolder(folder);
        std::this_thread::sleep_for(std::chrono::milliseconds(9+std::atoi(mineMessageUserFlag_.c_str())));
        log.info("ZAABLOKOWANYYYY");
    }
    log.info("AFTER WHILEEEEEEEEEEEEEEEeee");
    //sprawdzic czy tutaj dochodzimi
    std::unique_ptr<std::vector<std::string>> messagesFileContent = FileInterface::Accesor::getFileContent(chatFileWithPath_);
    auto fileContentIterator = messagesFileContent->end();
    if (messagesFileContent->size() == 1 && messagesFileContent->at(0) == "")
    {
        log.info("PUSTY PLIK");
        return true;
    }
    while(fileContentIterator != messagesFileContent->begin()) // dany wiersz jest do odbiorcy oraz został już przeczytany wcześniej
    {
        log.info("POBIERAM");
        --fileContentIterator;
        std::string messageFlag;
        messageFlag = *FileInterface::Accesor::getRowField(*fileContentIterator, FileStructure::LoggedFile::username); // TODO LoggedFile::username podmienic na odpowiedni stworzony przez mnowznia

        if(endOfMessageToRead(*fileContentIterator, messageFlag))
        {
            break;
        }
        else if(mineMessageUserFlag_ != messageFlag)
        {
            pushPurgeMessageOnStack(*fileContentIterator);
        }
    }
    bool updateFlagStatus = updateSeenFlags();

// ODBLOKOWUJEMY DOSTĘP DO FOLDERU TODO mwozniak
    FileInterface::unlockFolder(folder);

    return updateFlagStatus;
}

std::string Receiver::returnTheOldestMessage()
{
    if(purgeMessagesStack_.empty())
    {
        //return nullptr;
        return ""; //TODO mnurzyn czy rozsadnie w funkcji zwracajacej stringa zwracac w ifie nulltpr?
    }
    else
    {
        std::string message;
        message = purgeMessagesStack_.top();
        purgeMessagesStack_.pop();

        return message;
    }
}

bool Receiver::endOfMessageToRead(std::string message, std::string messageFlag)
{
    if( MessageFlags::seen == messageFlag)
    {
        std::string senderUsername;
        senderUsername = *FileInterface::Accesor::getRowField(message, FileStructure::LoggedFile::username); // TODO LoggedFile::username podmienic na odpowiedni stworzony przez mnowznia
        if( LocalUser::getLocalUser().getUsername() == senderUsername)
        {
            return true;
        }
    }
    return false;
}

std::string Receiver::purgeMessageFromRaw(std::string messageToPurge)
{
    auto firstCharToDelete = messageToPurge.begin() + 1;
    auto lastCharToDelete = messageToPurge.begin() + 18;
    messageToPurge.erase(firstCharToDelete, lastCharToDelete);

    return messageToPurge;
}

void Receiver::pushPurgeMessageOnStack(std::string rawMessageToPush)
{
    std::string purgeMessage;
    purgeMessage = purgeMessageFromRaw(rawMessageToPush);
    purgeMessagesStack_.push(purgeMessage);
}

bool Receiver::updateSeenFlags()
{
    bool updateFlagStatus;
    if(MessageFlags::inviter == mineMessageUserFlag_)
    {
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(chatFileWithPath_, MessageFlags::guest, MessageFlags::seen);
    }
    else if(MessageFlags::guest == mineMessageUserFlag_)
    {
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(chatFileWithPath_, MessageFlags::inviter, MessageFlags::seen);
    }
    return updateFlagStatus;
}
