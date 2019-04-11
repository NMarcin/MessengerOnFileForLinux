#include <thread>

#include "MessageTestCore.hpp"

void MessageFixture::SetUp()
{
    _expectedReadMessage = std::make_unique<std::string>("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    _expectedInviterMessage = std::make_unique<std::string>("[1][2019-03-21 08:41:30][mnurzyns][test inviter message]");
    _expectedRecipientMessage = std::make_unique<std::string>("[2][2019-03-21 08:41:30][mnurzyns][test recipient message]");
}

void MessageFixture::comparingExpectedMessageWithCreatedFromFullString(std::string expectedMessage)
{
    const Message message(expectedMessage);

    EXPECT_EQ(expectedMessage, message.messageToSave());
}

void MessageFixture::comparingExpectedTimeWithTimeFromMessage(std::string expectedMessage)
{
    const Message message(expectedMessage);
    const std::string expectedTime = "2019-03-21 08:41:30";

    EXPECT_EQ(expectedTime, message.getTime());
}

void MessageFixture::comparingExpectedUsernameWithUsernameFromMessage(std::string expectedMessage)
{
    const Message message(expectedMessage);
    const std::string expectedUsername = "mnurzyns";

    EXPECT_EQ(expectedUsername, message.getUsername());
}

void MessageFixture::comparingExpectedContentWithContentFromMessage(std::string expectedMessage, std::string messageKind)
{
    const Message message(expectedMessage);
    const std::string expectedReadContent = "test " + messageKind + " message";

    EXPECT_EQ(expectedReadContent, message.getContent());
}
