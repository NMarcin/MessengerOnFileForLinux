#include "FileGuardian.hpp"
#include "FileHandling.hpp"

bool guard::setFileFlag(const std::string & fileName, FileFlagType type, const std::string & pathToFile)
{    
    if (FileFlagType::guardian == type)
    {
        return createFile("GUARDIAN_" + fileName, pathToFile);
    }
    else if (FileFlagType::newFlag == type)
    {
        return createFile("newMessage", pathToFile);
    }
}

bool guard::removeFileFlag(const std::string & fileName, FileFlagType type, const std::string & pathToFile)
{
    if (FileFlagType::guardian == type)
    {
        return removeFile("GUARDIAN_" + fileName, pathToFile);
    }
    else if (FileFlagType::newFlag == type)
    {
        return removeFile("newMessage", pathToFile);
    }
}

bool guard::isGuardExist(const std::string & fileName, FileFlagType type, const std::string & pathToFile)
{
    if (FileFlagType::guardian == type)
    {
        return !isFileExists("GUARDIAN_" + fileName, pathToFile);
    }
    else if (FileFlagType::newFlag == type)
    {
        return removeFile("newMessage", pathToFile);
    }
}

