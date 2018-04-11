#pragma once
#include <string>
#include <memory>

#include <User.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

enum class AnswerType
{
    disaccepted,
    accepted
};

class ChatRequest
{
public:
    std::string answerForChatRequest(const std::string& ) const;
    std::string sendChatRequest(const std::string& username) const;

    ChatRequest();
    ~ChatRequest();

private:
    bool changeUserStatus(const User& user, const std::string& newStatus) const;
    std::unique_ptr<std::string> getChatFolderName(const std::string& folderName) const;
    std::unique_ptr<std::string> getUserStatus(const std::string& username) const;
    std::unique_ptr<std::string> getUsernameThroughPid(const int userPid) const;
    bool isUserActive(const User& user) const;
    bool respondOnInvitation() const;
    std::string sendAnswer(const std::string& senderUsername, AnswerType type) const;
    void sendSIGUSR1Signal(const int userPid) const;
    void showInvitation(const std::string& senderUsername) const;
    bool waitForAnswer(const std::string& username) const;

    Logger log {LogSpace::ChatFile};
};
