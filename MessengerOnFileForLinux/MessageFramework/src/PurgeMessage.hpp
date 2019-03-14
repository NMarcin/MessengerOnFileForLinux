#pragma once

#include <Message.hpp>

class PurgeMessage : public Message
{
public:
    std::string messageToShow() const;

    PurgeMessage(const Message& message);
    ~PurgeMessage() = default;

private:
    void setTime(std::string longTime);


    Logger log_ {LogSpace::MessageFramework};
};

// [09:19][tomek]: czesc, co u ciebie ?
