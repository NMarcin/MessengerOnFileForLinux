#pragma once
#include <string>

enum class FileFlagType
{
    guardian,
    newMessage,
    refuseChatInvitation,
    acceptChatInvitation
};

namespace FileFlag
{
bool isFlagExist(FileFlagType type, const std::string& pathToFile = "", const std::string& fileName = "");
bool setFileFlag(FileFlagType type, const std::string& pathToFile = "", const std::string& fileName = "");
bool removeFileFlag(FileFlagType type, const std::string& pathToFile = "", const std::string& fileName = "");
}
