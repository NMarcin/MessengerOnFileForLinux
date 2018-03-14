#pragma once
#include <string>
#include <memory>

#include <User.hpp>
#include <FileGuardian.hpp>

class ChatRequest
{
public:
    bool answerForChatRequest(const int usernamePid) const;
    bool sendChatRequest(const std::string& username) const;

    ChatRequest();
    ~ChatRequest();

private:
    bool isUserLogged(const std::string& username) const;
    bool changeUserStatus(const User& user, const std::string& newStatus) const;
    bool isUserActive(const User& user) const;
    std::unique_ptr<std::string> getUsernameByProcessId(const int userPid) const;
    bool makeDecision() const;
    void sendSigusr1Signal(const int userPid) const;
    void showInvitation(const std::string& senderUsername) const;
    bool sendAnswer(const std::string& senderUsername, FileFlagType type) const;
    bool waitForAnswer(const std::string& username) const;
};
