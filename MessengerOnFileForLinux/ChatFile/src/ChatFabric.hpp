#pragma once
#include <string>

class ChatFabric
{
public:
    bool createChatStructure(std::string usernameInviter, std::string usernameGuess);

private:
    bool createChatFolder(std::string usernameInviter, std::string usernameGuess);
    bool createChatFile(std::string usernameInviter, std::string usernameGuess);
    int getFreeFolderNumber();
};
