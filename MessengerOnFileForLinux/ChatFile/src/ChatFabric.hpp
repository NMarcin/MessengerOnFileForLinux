#pragma once
#include <string>

class ChatFabric
{
public:
    ChatFabric();
    ~ChatFabric();
    
    bool createChatStructure(const std::string& usernameInviter, const std::string& usernameGuess) const;

private:
    std::string createChatFolder(const std::string& usernameInviter, const std::string& usernameGuess) const;
    bool createChatFile(const std::string& chatFolderName, const std::string& usernameInviter, const std::string& usernameGuess) const;
    int getFreeFolderNumber(const std::string& folderPath) const;
};
