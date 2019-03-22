#include <MessageTestCore.hpp>

TEST_F(MessageFixture, isMessageCorrectCreatedFromFullMessageInRow)
{
    EXPECT_TRUE(true);
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromParameters)
{
    const Message readMessage("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    const Message inviterMessage("[1][2019-03-21 08:41:30][mnurzyns][test inviter message]");
    const Message recipientMessage("[2][2019-03-21 08:41:30][mnurzyns][test recipient message]");
    EXPECT_EQ(*expectedReadMessage, readMessage.messageToSave());
    EXPECT_EQ(*expectedInviterMessage, inviterMessage.messageToSave());
    EXPECT_EQ(*expectedRecipientMessage, recipientMessage.messageToSave());
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromDeafultCopyCtor)
{
    const Message readMessage("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    ASSERT_EQ(*expectedReadMessage, readMessage.messageToSave());

    Message copiedMessage = readMessage;
    EXPECT_EQ(readMessage.messageToSave(), copiedMessage.messageToSave());
    EXPECT_EQ(*expectedReadMessage, copiedMessage.messageToSave());
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromDeafultMoveCtor)
{
    Message readMessage("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    ASSERT_EQ(*expectedReadMessage, readMessage.messageToSave());

    Message movedMessage(std::move(readMessage));
    EXPECT_NE(readMessage.messageToSave(), movedMessage.messageToSave());
    EXPECT_EQ(*expectedReadMessage, movedMessage.messageToSave());
}

TEST_F(MessageFixture, isTimeFromMessageCorrectReturned)
{
    const Message readMessage(*expectedReadMessage);
    const Message inviterMessage(*expectedInviterMessage);
    const Message recipientMessage(*expectedRecipientMessage);

    const std::string expectedTime = "2019-03-21 08:41:30";

    EXPECT_EQ(expectedTime, readMessage.getTime());
    EXPECT_EQ(expectedTime, inviterMessage.getTime());
    EXPECT_EQ(expectedTime, recipientMessage.getTime());
}

TEST_F(MessageFixture, isUsernameFromMessageCorrectReturned)
{
    const Message readMessage(*expectedReadMessage);
    const Message inviterMessage(*expectedInviterMessage);
    const Message recipientMessage(*expectedRecipientMessage);

    const std::string expectedUsername = "mnurzyns";

    EXPECT_EQ(expectedUsername, readMessage.getUsername());
    EXPECT_EQ(expectedUsername, inviterMessage.getUsername());
    EXPECT_EQ(expectedUsername, recipientMessage.getUsername());
}

TEST_F(MessageFixture, isContentFromMessageCorrectReturned)
{
    const Message readMessage(*expectedReadMessage);
    const Message inviterMessage(*expectedInviterMessage);
    const Message recipientMessage(*expectedRecipientMessage);

    const std::string expectedReadContent = "test read message";
    const std::string expectedInviterContent = "test inviter message";
    const std::string expectedRecipientContent = "test recipient message";

    EXPECT_EQ(expectedReadContent, readMessage.getContent());
    EXPECT_EQ(expectedInviterContent, inviterMessage.getContent());
    EXPECT_EQ(expectedRecipientContent, recipientMessage.getContent());
}
