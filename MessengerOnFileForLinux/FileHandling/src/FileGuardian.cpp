#include <FileGuardian.hpp>
#include <FileHandling.hpp>

bool FileFlag::setFileFlag(FileFlagType type, const std::string & pathToFile, const std::string & fileName)
{    
    if (FileFlagType::guardian == type)
    {
        return FileInterface::createFile(fileName + "_GUARDIAN", pathToFile);
    }
    else if (FileFlagType::newMessage == type)
    {
        return FileInterface::createFile("newMessage", pathToFile);
    }
    else if (FileFlagType::refuseChatInvitation == type)
    {
        return FileInterface::createFile(fileName + "_REFUSE", pathToFile);
    }
    else if (FileFlagType::acceptChatInvitation == type)
    {
        return FileInterface::createFile(fileName + "_ACCEPT", pathToFile);
    }
}

bool FileFlag::removeFileFlag(FileFlagType type, const std::string & pathToFile, const std::string & fileName)
{
    if (FileFlagType::guardian == type)
    {
        return FileInterface::removeFile(fileName + "_GUARDIAN", pathToFile);
    }
    else if (FileFlagType::newMessage == type)
    {
        return FileInterface::removeFile("newMessage", pathToFile);
    }
    else if (FileFlagType::refuseChatInvitation == type)
    {
        return FileInterface::removeFile(fileName + "_REFUSE", pathToFile);
    }
    else if (FileFlagType::acceptChatInvitation == type)
    {
        return FileInterface::removeFile(fileName + "_ACCEPT", pathToFile);
    }
}

bool FileFlag::isFlagExist(FileFlagType type, const std::string & pathToFile, const std::string & fileName)
{
    if (FileFlagType::guardian == type)
    {
        return FileInterface::isFileExist(fileName + "_GUARDIAN", pathToFile);
    }
    else if (FileFlagType::newMessage == type)
    {
        return FileInterface::isFileExist("newMessage", pathToFile);
    }
    else if (FileFlagType::refuseChatInvitation == type)
    {
        return FileInterface::isFileExist(fileName + "_REFUSE", pathToFile);
    }
    else if (FileFlagType::acceptChatInvitation == type)
    {
        return FileInterface::isFileExist(fileName + "_ACCEPT", pathToFile);
    }
}

