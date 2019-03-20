#pragma once
#include <string>
#include <memory>

#include <Logger.hpp>
#include <LogSpace.hpp>
#include "UserInactivityDetector.hpp"

enum class AnswerType
{
    disaccepted,
    accepted
};

class ChatRequest
{
public:
    std::string answerForChatRequest(const std::string& senderUsername, const std::string& decision) const;
    std::string sendChatRequest(const std::string& receiverUsername) const;

    ChatRequest();
    ~ChatRequest();

    ChatRequest(ChatRequest &&) = delete;
    ChatRequest operator=(ChatRequest &&) = delete;
    ChatRequest(const ChatRequest &) = delete;
    ChatRequest operator=(const ChatRequest &) = delete;

private:
    bool changeUserStatus(const std::string& username, const std::string& newStatus) const;
    std::unique_ptr<std::string> getChatFolderName(const std::string& folderName) const;
    std::unique_ptr<std::string> getUserStatus(const std::string& username) const;
    bool isUserActive(const std::string& username) const;
    bool approveChatInvitation() const;
    std::string sendAnswer(const std::string& senderUsername, AnswerType type) const;
    void showInvitation(const std::string& senderUsername) const;
    bool waitForAnswer(const std::string& username) const;

    Logger log_ {LogSpace::ChatStarter};
};
