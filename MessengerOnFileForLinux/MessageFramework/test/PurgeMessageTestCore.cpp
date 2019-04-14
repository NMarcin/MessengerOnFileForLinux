#include "PurgeMessageTestCore.hpp"

void PurgeMessageFixture::SetUp()
{
    _expectedPurgeMessage = std::make_unique<std::string>("[08:41][mnurzyns][test message]");
    _message = std::make_unique<Message>("[0][2019-03-21 08:41:30][mnurzyns][test message]");
    ASSERT_EQ(_message->messageToSave(), "[0][2019-03-21 08:41:30][mnurzyns][test message]");
}
