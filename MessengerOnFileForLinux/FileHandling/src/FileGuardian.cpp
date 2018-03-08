#include "FileGuardian.hpp"
#include "FileHandling.hpp"

bool guard::setFileFlag(const std::string & fileName, FileFlagType type)
{
    if (FileFlagType::guardian == type)
    {
        return createFile("GUARDIAN_" + fileName);
    }
    else if (FileFlagType::newFlag == type)
    {
        return createFile("newMessage");
    }
}

bool guard::removeFileFlag(const std::string & fileName, FileFlagType type)
{
    if (FileFlagType::guardian == type)
    {
        return removeFile("GUARDIAN_" + fileName);
    }
    else if (FileFlagType::newFlag == type)
    {
        return removeFile("newMessage");
    }
}

bool guard::isGuardExist(const std::string & fileName, FileFlagType type)
{
    if (FileFlagType::guardian == type)
    {
        return !isFileExists("GUARDIAN_" + fileName);
    }
    else if (FileFlagType::newFlag == type)
    {
        return removeFile("newMessage");
    }
}
