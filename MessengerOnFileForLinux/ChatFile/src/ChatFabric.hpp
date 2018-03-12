#pragma once
#include <string>

class ChatFabric
{
public:
    bool createChatStructure(std::string usernameInviter, std::string usernameGuess);

private:
    std::string createChatFolder(std::string usernameInviter, std::string usernameGuess);
    bool createChatFile(std::string chatFolderName, std::string usernameInviter, std::string usernameGuess);
    int getFreeFolderNumber(std::string folderPath);
};
