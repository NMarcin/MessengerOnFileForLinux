#pragma once

#include <Message.hpp>

class PurgeMessage : public Message
{
public:
    std::string messageToShow() const;

    PurgeMessage(const Message& message);
    ~PurgeMessage() = default;

private:
    bool setTime(std::string longTime);
};

// [09:19][tomek]: czesc, co u ciebie ?
