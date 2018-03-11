#pragma once
#include <string>
#include <memory>

#include <User.hpp>

class ChatRequest
{
public:
    bool answerForChatRequest(const int usernamePid) const;
    bool sendChatRequest(const std::string& username) const;

    ChatRequest();
    ~ChatRequest();

private:
    bool changeUserStatus(const User & user, const std::string& newStatus) const;
    bool isUserActive(const User & user) const;
    std::unique_ptr< std::string> getUsernameByProcessId(const int userPid) const;
    void sendSigusr1Signal(const int userPid) const;


};

