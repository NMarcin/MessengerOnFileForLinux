#include <PurgeMessage.hpp>
#include <StringSum.hpp>

std::string PurgeMessage::messageToShow() const
{
    log_.function("PurgeMessage::messageToShow()");
    StringSumSquareBrackets fullMessage;

    fullMessage.sum(time_);
    fullMessage.sum(username_);
    fullMessage.sum(content_);

    return fullMessage.getSumedString();
}

PurgeMessage::PurgeMessage(const Message& message)
{
    log_.function("Message C-TOR from Message");
    setTime(message.getTime());              //time_ = setTime(message.getTime());
    username_ = message.getUsername();
    content_ = message.getContent();

}

bool PurgeMessage::setTime(std::string longTime)
{
    log_.function("PurgeMessage::setTime()");
    auto secondPosition = longTime.find_last_of(":");
    time_.append(longTime.begin(), longTime.begin() + secondPosition);
}
