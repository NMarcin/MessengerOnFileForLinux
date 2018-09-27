#include <PurgeMessage.hpp>
#include <StringSum.hpp>

std::string PurgeMessage::messageToShow() const
{
    log_.function("PurgeMessage::messageToShow() started");
    StringSumSquareBrackets fullMessage;

    fullMessage.sum(time_);
    fullMessage.sum(username_);
    fullMessage.sum(content_);

    auto messageToShow = fullMessage.getSumedString();

    log_.function("PurgeMessage::messageToShow() message = ");
    log_.debug(messageToShow);

    return messageToShow;
}

PurgeMessage::PurgeMessage(const Message& message)
{
    log_.function("Message C-TOR from Message");
    time_ = setTime(message.getTime());
    log_.function(time_);
    username_ = message.getUsername();
    content_ = message.getContent();
}

bool PurgeMessage::setTime(std::string longTime)
{
    log_.function("PurgeMessage::setTime() started");
    auto secondPosition = longTime.find_last_of(":");
    time_.append(longTime.begin(), longTime.begin() + secondPosition);
}
