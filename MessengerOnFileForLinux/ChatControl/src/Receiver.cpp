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

    if (isChatFileEmpty(messagesFileContent))
    {
        FileInterface::unlockFolder(folder);
        return false;
    }

    while(fileContentIterator != messagesFileContent->begin())
    {
        --fileContentIterator;
        std::string MessageFlags;
        MessageFlags = *FileInterface::Accesor::getRowField(*fileContentIterator, FileStructure::MessageFile::flag);
        if(endOfMessageToRead(*fileContentIterator, MessageFlags))
        {
            break;
        }
        else if(mineMessageUserFlag_ != MessageFlags && MessageFlags::seen != MessageFlags)
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
    pathToFolder = *FileInterface::Accesor::getFolderName(chatFileWithPath_);
    if(MessageFlags::inviter == mineMessageUserFlag_)
    {
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlags::guest);
    }
    else if(MessageFlags::guest == mineMessageUserFlag_)
    {
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlags::inviter);
    }
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

bool Receiver::endOfMessageToRead(std::string message, std::string MessageFlags)
{
    if( MessageFlags::seen == MessageFlags)
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

bool Receiver::isChatFileEmpty(std::unique_ptr<std::vector<std::string>>& chatFileContent)
{
    return chatFileContent->size() == 1 && chatFileContent->at(0) == "";
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
