#pragma once
#include <string>
#include <memory>

#include <User.hpp>

enum class AnswerType
{
    disaccepted,
    accepted
};

class ChatRequest
{
public:
    bool answerForChatRequest(const int usernamePid) const;
    bool sendChatRequest(const std::string& username) const;

    ChatRequest();
    ~ChatRequest();

private:
    bool changeUserStatus(const User& user, const std::string& newStatus) const;
    std::unique_ptr<std::string> getChatFolderName(const std::string& folderName) const;
    std::unique_ptr<std::string> getUsernameThroughPid(const int userPid) const;
    std::unique_ptr<std::string> getUserStatus(const std::string& username) const;
    bool isUserActive(const User& user) const;
    bool respondToInvitation() const;
    bool sendAnswer(const std::string& senderUsername, AnswerType type) const;
    void sendSigusr1Signal(const int userPid) const;
    void showInvitation(const std::string& senderUsername) const;
    bool waitForAnswer(const std::string& username) const;
};
