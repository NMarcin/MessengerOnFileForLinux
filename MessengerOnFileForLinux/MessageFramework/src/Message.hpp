#pragma once

#include<iostream>

enum class ChatRole
{
    inviter,
    recipient
};

enum class MessageFlag
{
    readMessage,
    inviterMessage,
    recipientMessage
};

class Message
{
public:
    std::string messageToSave();

    std::string getTime();
    std::string getUsername();
    std::string getContent();

    Message(MessageFlag messageFlag, std::string username, std::string content);
    ~Message() = default;

private:
    bool setMessageFlag(MessageFlag messageFlag);    // do kogo wiadomosc, a nie chatRole
    bool setUsername(std::string username);
    bool setContent(std::string content_);

    MessageFlag messageFlag_;
    std::string date_;
    std::string time_;
    std::string username_;
    std::string content_;

};

// [1][Jul 31 2018 | 09:19:13][tomek][czesc, co u ciebie ?]
