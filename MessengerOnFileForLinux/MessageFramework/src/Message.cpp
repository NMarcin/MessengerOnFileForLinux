#include <Message.hpp>
#include <string>
#include <StringSum.hpp>
#include <GlobalVariables.hpp>

Message::Message(std::string messageFlag, std::string username, std::string content)
{
    setMessageFlag(messageFlag);        // TODO mnurzyns use throw as false check
    setUsername(username);
    setContent(content);
}

std::string Message::messageToSave() const
{
    StringSumSquareBrackets fullMessage;

    fullMessage.sum(messageFlag_);
    fullMessage.sum(date_ + " | " + time_);
    fullMessage.sum(username_);
    fullMessage.sum(content_);

    return fullMessage.getSumedString();
}


bool Message::setMessageFlag(std::string messageFlag)
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
    //TODO mnurzyns mwoznia Czy na pewno chcemy to sprawdzać? Nie kazdy ma 8 znakowego username. Wezmy np. takiego biolika czy tomeczka
    //int requiredUsernameSize = 8; // for example 'mnurzyns'
    //if(username.size() == requiredUsernameSize)
    //{
        username_ = username;
        return true;
    //}
    //else
    //{
    //    return false;
    //}
}

bool Message::setContent(std::string content)
{
    int firstLetter = 1;
    int secondLetter = 2;
    if(content[firstLetter] != '/' && content[secondLetter] != '/')
    {
        content_ = content;
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

std::string Message::getContent()
{
    return content_;
}
