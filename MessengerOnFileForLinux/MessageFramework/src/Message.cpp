#include <Message.hpp>
#include <string>
#include <StringSum.hpp>
#include <GlobalVariables.hpp>
#include "DateManagment.hpp"

#include <vector>

Message::Message(std::string messageFlag, std::string username, std::string content)
{
    log_.function("Message C-TOR string x3");
    setMessageFlag(messageFlag);
    username_ = username;
    setContent(content);
    time_ = DataManagment::convertDateToString(DataManagment::getActualDate());
}

Message::Message(std::string fullMessageInRow)
{
    log_.function("Message C-TOR longString");
    messageFlag_.append( fullMessageInRow.begin() + 1,  fullMessageInRow.begin() + 2  );
    time_.append(        fullMessageInRow.begin() + 4, fullMessageInRow.begin() + 24 );
    username_.append(    fullMessageInRow.begin() + 27, fullMessageInRow.begin() + 35 );
    content_.append(     fullMessageInRow.begin() + 37, fullMessageInRow.end()   - 1  );
}

std::string Message::messageToSave() const
{
    log_.function("Message::messageToSave() started");
    StringSumSquareBrackets fullMessage;

    fullMessage.sum(messageFlag_);
    fullMessage.sum(time_);
    fullMessage.sum(username_);
    fullMessage.sum(content_);

    return fullMessage.getSumedString();
}


bool Message::setMessageFlag(std::string messageFlag)
{
    log_.function("Message::setMessageFlag()");
    if(MessageFlag::inviterMessage == messageFlag || MessageFlag::recipientMessage == messageFlag)
    {
        std::string logData = "Message::setMessageFlag() messageFlag_ set as " + messageFlag;
        log_.info(logData);
        messageFlag_ = messageFlag;
        return true;
    }
    else if (MessageFlag::readMessage == messageFlag)
    {
        log_.info("Message::setMessageFlag() message read, can not unread");
        return false;
    }
}

bool Message::setContent(std::string content)
{
    log_.function("Message::setContent()");
    int firstLetter = 1;
    int secondLetter = 2;
    if(content[firstLetter] != '/' && content[secondLetter] != '/')
    {
        content_ = content;
        log_.info("Message::setMessageFlag() content of message set");
        return true;
    }
    else
    {
        log_.info("Message::setMessageFlag() it's not message, it's terminal command");
        return false;
    }
}

std::string Message::getTime() const
{
    log_.function("Message::getTime()");
    return time_;
}

std::string Message::getUsername() const
{
    log_.function("Message::getUsername()");
    return username_;
}

std::string Message::getContent() const
{
    log_.function("Message::getContent()");
    return content_;
}
