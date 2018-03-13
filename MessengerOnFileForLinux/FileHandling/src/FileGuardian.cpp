#include <FileGuardian.hpp>
#include <FileHandling.hpp>

bool FileFlag::setFileFlag(FileFlagType type, const std::string & pathToFile, const std::string & fileName)
{    
    if (FileFlagType::guardian == type)
    {
        return FileInterface::createFile("GUARDIAN_" + fileName, pathToFile);
    }
    else if (FileFlagType::newMessage == type)
    {
        return FileInterface::createFile("newMessage", pathToFile);
    }
    else if (FileFlagType::refuseChatInvitation == type)
    {
        return FileInterface::createFile("refusal", pathToFile);
    }
}

bool FileFlag::removeFileFlag(FileFlagType type, const std::string & pathToFile, const std::string & fileName)
{
    if (FileFlagType::guardian == type)
    {
        return FileInterface::removeFile("GUARDIAN_" + fileName, pathToFile);
    }
    else if (FileFlagType::newMessage == type)
    {
        return FileInterface::removeFile("newMessage", pathToFile);
    }
    else if (FileFlagType::refuseChatInvitation == type)
    {
        return FileInterface::removeFile("refusal", pathToFile);
    }
}

bool FileFlag::isFlagExist(FileFlagType type, const std::string & pathToFile, const std::string & fileName)
{
    if (FileFlagType::guardian == type)
    {
        return FileInterface::isFileExists("GUARDIAN_" + fileName, pathToFile);
    }
    else if (FileFlagType::newMessage == type)
    {
        return FileInterface::isFileExists("newMessage", pathToFile);
    }
    else if (FileFlagType::refuseChatInvitation == type)
    {
        return FileInterface::isFileExists("refusal", pathToFile);
    }
}

