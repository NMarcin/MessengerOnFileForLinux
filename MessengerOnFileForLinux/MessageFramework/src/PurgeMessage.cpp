#include <PurgeMessage.hpp>
#include <StringSum.hpp>

std::string PurgeMessage::messageToShow() const
{
    _log.function("PurgeMessage::messageToShow() started");
    StringSumSquareBrackets fullMessage;

    fullMessage.sum(_time);
    fullMessage.sum(_username);
    fullMessage.sum(_content);

    auto messageToShow = fullMessage.getSumedString();

    _log.function("PurgeMessage::messageToShow() message = ");
    _log.debug(messageToShow);

    return messageToShow;
}

PurgeMessage::PurgeMessage(const Message& message)
{
    _log.function("Message C-TOR from Message");
    setTime(message.getTime());
    _log.function(_time);
    _username = message.getUsername();
    _content = message.getContent();
}

void PurgeMessage::setTime(const std::string& longTime)
{
    _log.function("PurgeMessage::setTime() started");
    std::string logtime= "PurgeMessage::setTime() longTime = " + longTime;
    _log.info(logtime);
    auto secondPosition = longTime.find_last_of(":");
    _time.append(longTime.begin()+11, longTime.begin() + secondPosition);
    _log.function("PurgeMessage::setTime() ended");
}
