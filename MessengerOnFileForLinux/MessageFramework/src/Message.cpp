#include <Message.hpp>




Message::Message(MessageFlag messageFlag, std::string username, std::string message);
{
    setMessageFlag(messageFlag);
    setUsername(username);
    setMessage(message);
}

std::string Message::messageToSave()
{
    // stringłącznik
}


bool Message::setMessageFlag(MessageFlag messageFlag)
{
    if(MessageFlag::inviterMessage == messageFlag || MessageFlag::recipientMessage == messageFlag)
    {
        messageFlag_ = messageFlag;
        return true;
    }
    else if (MessageFlag::readMessage == messageFlag)
    {
        return false; // wiadomosc byla juz odczytana
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
