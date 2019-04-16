#include "Receiver.hpp"
#include "PurgeMessage.hpp"
#include "GlobalVariables.hpp"
#include "FileHandling.hpp"

#include <thread>
#include <chrono>

Receiver::Receiver(std::shared_ptr<ChatInformation> chatInfo)
                : _chatInfo(chatInfo)
{
    //NOOP
}

bool Receiver::readMessagesToStack()
{
    _log.function("Receiver::readMessagesToStack() started");
    auto folder = *FileInterface::Accesor::getFolderName(_chatInfo->_chatPath);
    FileInterface::lockFolder(folder);

    std::unique_ptr<std::vector<std::string>> messagesFileContent = FileInterface::Accesor::getFileContent(_chatInfo->_chatPath, AccesMode::withoutGuardian);
    auto fileContentIterator = messagesFileContent->end();

    if (isChatFileEmpty(messagesFileContent))
    {
        FileInterface::unlockFolder(folder);
        _log.info("Receiver::readMessagesToStack() ChatFolder is empty, unlocking folder");
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
        else if(_chatInfo->_messageFlag != messageFlag && MessageFlag::readMessage != messageFlag)
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
    _log.function("Receiver::removeFlagNEW() started");
    std::string pathToFolder;
    pathToFolder = *FileInterface::Accesor::getFolderName(_chatInfo->_chatPath);
    if(MessageFlag::inviterMessage == _chatInfo->_messageFlag)
    {
        _log.info("Receiver::removeFlagNEW() remove flag 'NEW' create by recipient");
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlag::recipientMessage);
    }
    else if(MessageFlag::recipientMessage == _chatInfo->_messageFlag)
    {
        _log.info("Receiver::removeFlagNEW() remove flag 'NEW' create by inviter");
        FileInterface::Managment::removeFile(pathToFolder + "/NEW" + "_" + MessageFlag::inviterMessage);
    }
}

std::unique_ptr<PurgeMessage> Receiver::returnTheOldestMessage()
{
    _log.function("Receiver::returnTheOldestMessage() started");
    if(_purgeMessagesStack.empty())
    {
        _log.info("Receiver::returnTheOldestMessage() purgeMessageStack is empty");
        return nullptr;
    }
    else
    {
        std::unique_ptr<PurgeMessage> purgeMessage;
        purgeMessage = std::make_unique<PurgeMessage>(_purgeMessagesStack.top());
        _purgeMessagesStack.pop();

        _log.info("Receiver::returnTheOldestMessage() purgeMessage returned and pop from purgeMessageStack");
        return purgeMessage;
    }
}

bool Receiver::endOfMessageToRead(std::string message, std::string messageFlag)
{
    _log.function("Receiver::endOfMessageToRead() started");
    if( MessageFlag::readMessage == messageFlag)
    {
        std::string senderUsername;
        senderUsername = *FileInterface::Accesor::getRowField(message, FileStructure::MessageFile::flag);
        if(LOCAL_USER == senderUsername)
        {
            _log.info("Receiver::endOfMessageToRead() Message read befory by user, end of reading messages");
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
    _log.function("Receiver::messagePurging() started ");
    std::unique_ptr<PurgeMessage> purgeMessage= std::make_unique<PurgeMessage>(messageToPurge);
    return purgeMessage;
}

void Receiver::pushPurgeMessageOnStack(std::string rawMessageToPush)
{
    _log.function("Receiver::pushPurgeMessageOnStack() started, rawMessageToPush: ");
    _log.debug(rawMessageToPush);
    if( "" != rawMessageToPush)
    {
        Message message(rawMessageToPush);
        auto purgeMessage = messagePurging(message);
        _purgeMessagesStack.push(*purgeMessage);
    }
    else
    {
        _log.info("Receiver::pushPurgeMessageOnStack() message empty");
    }
}

bool Receiver::updateSeenFlags()
{
    _log.function("Receiver::updateSeenFlags() started");
    bool updateFlagStatus = false;
    if(MessageFlag::inviterMessage == _chatInfo->_messageFlag)
    {
        _log.info("Receiver::updateSeenFlags() update flag status for MessageFlag::recipientMessage = 0");
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(_chatInfo->_chatPath, MessageFlag::recipientMessage, MessageFlag::readMessage);
    }
    else if(MessageFlag::recipientMessage == _chatInfo->_messageFlag)
    {
        _log.info("Receiver::updateSeenFlags() update flag status for MessageFlag::inviterMessage = 0");
        updateFlagStatus = FileInterface::Modification::updateFlagsInFile(_chatInfo->_chatPath, MessageFlag::inviterMessage, MessageFlag::readMessage);
    }
    return updateFlagStatus;
}
