#include "Receiver.hpp"

Receiver::Receiver()
{
    //NOOP
}

Receiver::~Receiver()
{
    //NOOP
}


bool Receiver::getRawMessagesFromFile(std::string chatFileWithPath)
{
    return false;
}

std::string Receiver::getMessageFromStack()
{
    return "false";
}

std::string Receiver::purgeMessage(std::string rawMessage)
{
    return "false";
}

bool Receiver::addMessageToQueue(std::queue<std::string> messagesToShowOnScreen, std::string purgeMessage)
{
    return false;
}
