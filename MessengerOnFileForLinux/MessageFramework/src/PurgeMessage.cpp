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
    time_ = setTime(message.getTime());
    log_.function(time_);
    username_ = message.getUsername();
    content_ = message.getContent();
}

bool PurgeMessage::setTime(std::string longTime)
{
    auto z = "PurgeMessage::setTime() TIME = " + longTime;
    log_.function(z);
    auto secondPosition = longTime.find_last_of(":");
    log_.function("PurgeMessage::setTime() KONIEC");
    time_.append(longTime.begin(), longTime.begin() + secondPosition);
    log_.function("PurgeMessage::setTime() KONIEC111");
}
