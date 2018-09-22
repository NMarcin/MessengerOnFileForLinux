#include <Receiver.hpp>

#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <PurgeMessage.hpp>

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
        std::string messageFlag;
        messageFlag = *FileInterface::Accesor::getRowField(*fileContentIterator, FileStructure::MessageFile::flag);
        if(endOfMessageToRead(*fileContentIterator, messageFlag))
        {
            break;
        }
        else if(mineMessageUserFlag_ != messageFlag && MessageFlag::readMessage != messageFlag)
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
    if(MessageFlag::inviterMessage == mineMessageUserFlag_)
    {
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlag::recipientMessage);
    }
    else if(MessageFlag::recipientMessage == mineMessageUserFlag_)
    {
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlag::inviterMessage);
    }
}

std::unique_ptr<PurgeMessage> Receiver::returnTheOldestMessage()
{
    if(purgeMessagesStack_.empty())
    {
        return nullptr;
    }
    else
    {
        std::unique_ptr<PurgeMessage> purgeMessage;
        purgeMessage = std::make_unique<PurgeMessage>(purgeMessagesStack_.top());
        purgeMessagesStack_.pop();

        return purgeMessage;
    }
}

bool Receiver::endOfMessageToRead(std::string message, std::string messageFlag)
{
    if( MessageFlag::readMessage == messageFlag)
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

std::unique_ptr<PurgeMessage> Receiver::messagePurging(Message& messageToPurge)
{
    std::unique_ptr<PurgeMessage> purgeMessage= std::make_unique<PurgeMessage>(messageToPurge);
    return purgeMessage;
    /*
    auto username = *FileInterface::Accesor::getRowField(messageToPurge, FileStructure::MessageFile::username);
    auto message = *FileInterface::Accesor::getRowField(messageToPurge, FileStructure::MessageFile::message);
    return username + " >> " + message; */
}

void Receiver::pushPurgeMessageOnStack(std::string rawMessageToPush)
{
    if( "" != rawMessageToPush)
    {
        Message message(rawMessageToPush);
        auto purgeMessage = messagePurging(message);
        purgeMessagesStack_.push(*purgeMessage);
    }
    /*
    if (rawMessageToPush != "")
    {
        std::string purgeMessage;
        purgeMessage = purgeMessageFromRaw(rawMessageToPush);
        purgeMessagesStack_.push(purgeMessage);
    }*/
}

bool Receiver::updateSeenFlags()
{
    bool updateFlagStatus;
    if(MessageFlag::inviterMessage == mineMessageUserFlag_)
    {
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(chatFileWithPath_, MessageFlag::recipientMessage, MessageFlag::readMessage);
    }
    else if(MessageFlag::recipientMessage == mineMessageUserFlag_)
    {
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(chatFileWithPath_, MessageFlag::inviterMessage, MessageFlag::readMessage);
    }
    return updateFlagStatus;
}
