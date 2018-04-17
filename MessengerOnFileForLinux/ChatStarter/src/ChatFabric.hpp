#pragma once
#include <string>
#include <Logger.hpp>
#include <LogSpace.hpp>


class ChatFabric
{
public:
    ChatFabric();
    ~ChatFabric();

    std::string createChatStructure(const std::string& usernameInviter, const std::string& usernameGuess) const;

private:
    std::string createChatFolder(const std::string& usernameInviter, const std::string& usernameGuess) const;
    std::string createChatFile(const std::string& chatFolderName, const std::string& usernameInviter, const std::string& usernameGuess) const;
    int getFreeFolderNumber() const;
    std::vector<int> getBusyNumbers() const;
    int findMissingNumber(std::vector<int>& busyNumbers_) const;

    Logger log {LogSpace::ChatFile};
};
