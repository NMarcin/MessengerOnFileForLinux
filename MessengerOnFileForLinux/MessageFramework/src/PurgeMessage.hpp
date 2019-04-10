#pragma once

#include <Message.hpp>

class PurgeMessage : protected Message
{
public:
    std::string messageToShow() const;

    PurgeMessage(const Message& message);
    ~PurgeMessage() = default;
    PurgeMessage(PurgeMessage &&) = default;
    PurgeMessage& operator=(PurgeMessage &&) = default;
    PurgeMessage(const PurgeMessage &) = default;
    PurgeMessage& operator=(const PurgeMessage &) = default;

private:
    void setTime(const std::string& longTime);


    Logger log_ {LogSpace::MessageFramework};
};

// [09:19][tomek]: czesc, co u ciebie ?
