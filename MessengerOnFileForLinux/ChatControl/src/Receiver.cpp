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
    /*//BLOKUJEMY DOSTĘP DO FOLDERU TODO mwozniak
    auto isFileLock = false;
    auto folder = *FileInterface::Accesor::getFolderName(chatFileWithPath_);
    while (!isFileLock)
    {
        isFileLock = FileInterface::lockFolder(folder);
        std::this_thread::sleep_for(std::chrono::milliseconds(9+std::atoi(mineMessageUserFlag_.c_str())));
        log.info("ZAABLOKOWANYYYY");
    }
    */

    std::unique_ptr<std::vector<std::string>> messagesFileContent = FileInterface::Accesor::getFileContent(chatFileWithPath_);
    auto fileContentIterator = messagesFileContent->end();

    if (messagesFileContent->size() == 1 && messagesFileContent->at(0) == "")//TODO mawoznia do funkcji albo zmienic getFileContent
    {
        log.info("PUSTY PLIK");
        return true;
    }
    while(fileContentIterator != messagesFileContent->begin())
    {
        --fileContentIterator;
        std::string messageFlag;
        messageFlag = *FileInterface::Accesor::getRowField(*fileContentIterator, FileStructure::MessageFile::flag);
        if(endOfMessageToRead(*fileContentIterator, messageFlag))
        {
            break;
        }
        else if(mineMessageUserFlag_ != messageFlag && MessageFlags::seen != messageFlag)
        {
            pushPurgeMessageOnStack(*fileContentIterator);
        }
    }
    bool updateFlagStatus = updateSeenFlags();

    //ODBLOKOWUJEMY DOSTĘP DO FOLDERU TODO mwozniak
    //FileInterface::unlockFolder(folder);

    return updateFlagStatus;
}

std::string Receiver::returnTheOldestMessage()
{
    log.info("ZCZYTUJE WIADOMOSCI");
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
        senderUsername = *FileInterface::Accesor::getRowField(message, FileStructure::MessageFile::flag);
        if( LocalUser::getLocalUser().getUsername() == senderUsername)
        {
            return true;
        }
    }
    return false;
}

std::string Receiver::purgeMessageFromRaw(std::string messageToPurge)
{
    auto username = *FileInterface::Accesor::getRowField(messageToPurge, FileStructure::MessageFile::username);
    auto message = *FileInterface::Accesor::getRowField(messageToPurge, FileStructure::MessageFile::message);
    return username + " >> " + message;
}

void Receiver::pushPurgeMessageOnStack(std::string rawMessageToPush)
{
    if (rawMessageToPush != "")
    {
        std::string purgeMessage;
        purgeMessage = purgeMessageFromRaw(rawMessageToPush);
        purgeMessagesStack_.push(purgeMessage);
    }
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
