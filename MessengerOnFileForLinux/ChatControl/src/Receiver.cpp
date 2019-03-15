#include <Receiver.hpp>

#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <FileHandling.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <PurgeMessage.hpp>

Receiver::Receiver(std::shared_ptr<ChatInformation> chatInfo)
                : chatInfo_(chatInfo)
{
    //NOOP
}

bool Receiver::readMessagesToStack()
{
    log_.function("Receiver::readMessagesToStack() started");
    auto folder = *FileInterface::Accesor::getFolderName(chatInfo_->chatPath_);
    FileInterface::lockFolder(folder);

    std::unique_ptr<std::vector<std::string>> messagesFileContent = FileInterface::Accesor::getFileContent(chatInfo_->chatPath_, AccesMode::withoutGuardian);
    auto fileContentIterator = messagesFileContent->end();

    if (isChatFileEmpty(messagesFileContent))
    {
        FileInterface::unlockFolder(folder);
        log_.info("Receiver::readMessagesToStack() ChatFolder is empty, unlocking folder");
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
        else if(chatInfo_->messageFlag_ != messageFlag && MessageFlag::readMessage != messageFlag)
        {
            pushPurgeMessageOnStack(*fileContentIterator);
        }
    }
    bool updateFlagStatus = updateSeenFlags();
    removeFlagNEW();
    FileInterface::unlockFolder(folder);

    return updateFlagStatus;
}

void Receiver::removeFlagNEW()
{
    log_.function("Receiver::removeFlagNEW() started");
    std::string pathToFolder;
    pathToFolder = *FileInterface::Accesor::getFolderName(chatInfo_->chatPath_);
    if(MessageFlag::inviterMessage == chatInfo_->messageFlag_)
    {
        log_.info("Receiver::removeFlagNEW() remove flag 'NEW' create by recipient");
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlag::recipientMessage);
    }
    else if(MessageFlag::recipientMessage == chatInfo_->messageFlag_)
    {
        log_.info("Receiver::removeFlagNEW() remove flag 'NEW' create by inviter");
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlag::inviterMessage);
    }
}

std::unique_ptr<PurgeMessage> Receiver::returnTheOldestMessage()
{
    log_.function("Receiver::returnTheOldestMessage() started");
    if(purgeMessagesStack_.empty())
    {
        log_.info("Receiver::returnTheOldestMessage() purgeMessageStack is empty");
        return nullptr;
    }
    else
    {
        std::unique_ptr<PurgeMessage> purgeMessage;
        purgeMessage = std::make_unique<PurgeMessage>(purgeMessagesStack_.top());
        purgeMessagesStack_.pop();

        log_.info("Receiver::returnTheOldestMessage() purgeMessage returned and pop from purgeMessageStack");
        return purgeMessage;
    }
}

bool Receiver::endOfMessageToRead(std::string message, std::string messageFlag)
{
    log_.function("Receiver::endOfMessageToRead() started");
    if( MessageFlag::readMessage == messageFlag)
    {
        std::string senderUsername;
        senderUsername = *FileInterface::Accesor::getRowField(message, FileStructure::MessageFile::flag);
        if( LocalUser::getLocalUser().getUsername() == senderUsername)
        {
            log_.info("Receiver::endOfMessageToRead() Message read befory by user, end of reading messages");
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
    log_.function("Receiver::messagePurging() started ");
    std::unique_ptr<PurgeMessage> purgeMessage= std::make_unique<PurgeMessage>(messageToPurge);
    return purgeMessage;
}

void Receiver::pushPurgeMessageOnStack(std::string rawMessageToPush)
{
    log_.function("Receiver::pushPurgeMessageOnStack() started, rawMessageToPush: ");
    log_.debug(rawMessageToPush);
    if( "" != rawMessageToPush)
    {
        Message message(rawMessageToPush);
        auto purgeMessage = messagePurging(message);
        purgeMessagesStack_.push(*purgeMessage);
    }
    else
    {
        log_.info("Receiver::pushPurgeMessageOnStack() message empty");
    }
}

bool Receiver::updateSeenFlags()
{
    log_.function("Receiver::updateSeenFlags() started");
    bool updateFlagStatus = false;
    if(MessageFlag::inviterMessage == chatInfo_->messageFlag_)
    {
        log_.info("Receiver::updateSeenFlags() update flag status for MessageFlag::recipientMessage = 0");
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(chatInfo_->chatPath_, MessageFlag::recipientMessage, MessageFlag::readMessage);
    }
    else if(MessageFlag::recipientMessage == chatInfo_->messageFlag_)
    {
        log_.info("Receiver::updateSeenFlags() update flag status for MessageFlag::inviterMessage = 0");
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(chatInfo_->chatPath_, MessageFlag::inviterMessage, MessageFlag::readMessage);
    }
    return updateFlagStatus;
}
