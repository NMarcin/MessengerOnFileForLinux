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

    auto folder = *FileInterface::Accesor::getFolderName(chatFileWithPath_);
    FileInterface::lockFolder(folder);

    std::unique_ptr<std::vector<std::string>> messagesFileContent = FileInterface::Accesor::getFileContent(chatFileWithPath_, AccesMode::withoutGuardian);
    auto fileContentIterator = messagesFileContent->end();

    if (messagesFileContent->size() == 1 && messagesFileContent->at(0) == "")//TODO mawoznia do funkcji albo zmienic getFileContent
    {
        log.info("PUSTY PLIK");
        FileInterface::unlockFolder(folder);
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
    removeFlagNEW();
    FileInterface::unlockFolder(folder);

    return updateFlagStatus;
}

bool Receiver::removeFlagNEW()
{
    std::string pathToFolder;
    pathToFolder = getFolderPath();
    if(MessageFlags::inviter == mineMessageUserFlag_)
    {
        FileInterface::Managment::removeFile(pathToFolder + "_" + MessageFlags::guest);
    }
    else if(MessageFlags::guest == mineMessageUserFlag_)
    {
        FileInterface::Managment::removeFile(pathToFolder + "_" + MessageFlags::inviter);
    }
}

std::string Receiver::getFolderPath() // TODO mwoznia <- to chyba warto przenieść do FileHandling
{
    std::string pathToFolder = chatFileWithPath_;
    auto lastSlash = pathToFolder.find_last_of("/");
    pathToFolder.erase(lastSlash+1);

    return pathToFolder;
}

std::string Receiver::returnTheOldestMessage()
{
    if(purgeMessagesStack_.empty())
    {
        return "";
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
