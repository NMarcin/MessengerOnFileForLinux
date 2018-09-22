#pragma once

#include<iostream>
#include <memory>

enum class ChatRole
{
    inviter,
    recipient
};

class Message
{
public:
    std::string messageToSave() const;

    std::string getTime() const;
    std::string getUsername() const;
    std::string getContent() const;

    Message(std::string messageFlag, std::string username, std::string content);
    Message(std::string fullMessageInRow);
    virtual ~Message() = default;

protected:
    std::string time_;
    std::string username_;
    std::string content_;

    Message() = default;

private:
    bool setMessageFlag(std::string messageFlag);    // do kogo wiadomosc, a nie chatRole
    bool setUsername(std::string username);
    bool setContent(std::string content);

    std::string messageFlag_;
    std::string date_;

};

// [1][Jul 31 2018 | 09:19:13][mnurzyns][czesc, co u ciebie ?]
