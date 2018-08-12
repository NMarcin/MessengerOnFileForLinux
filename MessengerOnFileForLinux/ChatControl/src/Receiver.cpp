#include <Receiver.hpp>

#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

Reciver::Reciver(std::string chatFileWithPath, std::string mineMessageUserFlag)
                : chatFileWithPath_(chatFileWithPath)
                , mineMessageUserFlag_(mineMessageUserFlag)
{
    //NOOP
}

Reciver::~Reciver()
{
    //NOOP
}

bool Reciver::readMessagesToStack()
{
// BLOKUJEMY DOSTĘP DO FOLDERU TODO mwozniak

    std::unique_ptr<std::vector<std::string>> messagesFileContent = FileInterface::Accesor::getFileContent(chatFileWithPath_);
    auto fileContentIterator = messagesFileContent->end();
    while(fileContentIterator != messagesFileContent->begin()) // dany wiersz jest do odbiorcy oraz został już przeczytany wcześniej
    {
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

    return updateFlagStatus;
}

std::string Reciver::returnTheOldestMessage()
{
    if(purgeMessagesStack_.empty())
    {
        return nullptr;
    }
    else
    {
        std::string message;
        message = purgeMessagesStack_.top();
        purgeMessagesStack_.pop();

        return message;
    }
}

bool Reciver::endOfMessageToRead(std::string message, std::string messageFlag)
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

std::string Reciver::purgeMessageFromRaw(std::string messageToPurge)
{
    auto firstCharToDelete = messageToPurge.begin() + 1;
    auto lastCharToDelete = messageToPurge.begin() + 18;
    messageToPurge.erase(firstCharToDelete, lastCharToDelete);

    return messageToPurge;
}

void Reciver::pushPurgeMessageOnStack(std::string rawMessageToPush)
{
    std::string purgeMessage;
    purgeMessage = purgeMessageFromRaw(rawMessageToPush);
    purgeMessagesStack_.push(purgeMessage);
}

bool Reciver::updateSeenFlags()
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
