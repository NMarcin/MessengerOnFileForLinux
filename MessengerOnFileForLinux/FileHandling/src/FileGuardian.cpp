#include "FileGuardian.hpp"
#include "FileHandling.hpp"



bool Guard::setFileFlag(const std::string & fileName, FileFlagType type, const std::string & pathToFile)
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

bool Guard::removeFileFlag(const std::string & fileName, FileFlagType type, const std::string & pathToFile)
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

bool Guard::isGuardExist(const std::string & fileName, FileFlagType type, const std::string & pathToFile)
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

