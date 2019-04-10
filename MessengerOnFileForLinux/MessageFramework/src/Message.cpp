#include <Message.hpp>
#include <string>
#include <StringSum.hpp>
#include <GlobalVariables.hpp>
#include "TimeManagment.hpp"

#include <vector>

Message::Message(const std::string& messageFlag, const std::string& username, const std::string& content)
{
    _log.function("Message C-TOR string x3");
    setMessageFlag(messageFlag);
    _username = username;
    setContent(content);
    _time = TimeManagment::convertTimeToString(TimeManagment::getLocalTime());
}

Message::Message(const std::string& fullMessageInRow)
{
    _log.function("Message C-TOR longString");
    _messageFlag.append( fullMessageInRow.begin() + 1,  fullMessageInRow.begin() + 2  );
    _time.append(        fullMessageInRow.begin() + 4, fullMessageInRow.begin() + 23 );
    _username.append(    fullMessageInRow.begin() + 25, fullMessageInRow.begin() + 33 );
    _content.append(     fullMessageInRow.begin() + 35, fullMessageInRow.end()   - 1  );
}

std::string Message::messageToSave() const
{
    _log.function("Message::messageToSave() started");
    StringSumSquareBrackets fullMessage;

    fullMessage.sum(_messageFlag);
    fullMessage.sum(_time);
    fullMessage.sum(_username);
    fullMessage.sum(_content);

    return fullMessage.getSumedString();
}

bool Message::setMessageFlag(const std::string& messageFlag)
{
    _log.function("Message::setMessageFlag()");
    _messageFlag = messageFlag;
    if(MessageFlag::inviterMessage == messageFlag || MessageFlag::recipientMessage == messageFlag)
    {
        std::string logData = "Message::setMessageFlag() messageFlag_ set as " + messageFlag;
        _log.info(logData);
        return true;
    }
    else if (MessageFlag::readMessage == messageFlag)
    {
        _log.info("Message::setMessageFlag() message read, can not unread");
        return false;
    }
    else
    {
        _log.info("Message::setMessageFlag() messageFlag unknown, error");
        return false;
    }
}

bool Message::setContent(const std::string& content)
{
    _log.function("Message::setContent()");
    int firstLetter = 1;
    int secondLetter = 2;
    if(content[firstLetter] != '/' && content[secondLetter] != '/')
    {
        _content = content;
        _log.info("Message::setMessageFlag() content of message set");
        return true;
    }
    else
    {
        _log.info("Message::setMessageFlag() it's not message, it's terminal command");
        return false;
    }
}

std::string Message::getTime() const
{
    _log.function("Message::getTime()");
    return _time;
}

std::string Message::getUsername() const
{
    _log.function("Message::getUsername()");
    return _username;
}

std::string Message::getContent() const
{
    _log.function("Message::getContent()");
    return _content;
}
