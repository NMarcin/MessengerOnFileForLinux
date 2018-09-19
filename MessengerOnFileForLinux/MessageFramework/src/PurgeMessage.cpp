#include <PurgeMessage.hpp>
#include <StringSum.hpp>

std::string PurgeMessage::messageToShow() const
{
    StringSumSquareBrackets fullMessage;

    fullMessage.sum(time_);
    fullMessage.sum(username_);
    fullMessage.sum(content_);

    return fullMessage.getSumedString();
}

PurgeMessage::PurgeMessage(const Message& message)
{
    time_ = message.getTime();
    username_ = message.getUsername();
    content_ = message.getContent();

}

bool PurgeMessage::setTime(std::string longTime)
{

}
