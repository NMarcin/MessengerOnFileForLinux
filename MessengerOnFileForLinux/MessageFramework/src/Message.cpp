#include <Message.hpp>

bool Message::setChatRole(ChatRole chatRole)
{
    if(ChatRole::inviter == chatRole || ChatRole::recipient == chatRole)
    {
        chatRole_ = chatRole;
        return true;
    }
    else
    {
        return false;
    }
}

bool Message::setUsername(std::string username)
{
    int requiredUsernameSize = 8; // for example 'mnurzyns'
    if(username.size() == requiredUsernameSize)
    {
        username_ = username;
        return true;
    }
    else
    {
        return false;
    }
}

bool Message::setMessage(std::string message)
{
    int firstLetter = 1;
    int secondLetter = 2;
    if(message[firstLetter] != '/' && message[secondLetter] != '/')
    {
        message_ = message;
        return true;
    }
    else
    {
        // it's not message, it's terminal command!
        return false;
    }
}

ChatRole Message::getChatRole()
{
    return chatRole_;
}

std::string Message::getDate()
{
    return date_;
}

std::string Message::getTime()
{
    return time_;
}

std::string Message::getUsername()
{
    return username_;
}

std::string Message::getMessage()
{
    return message_;
}
