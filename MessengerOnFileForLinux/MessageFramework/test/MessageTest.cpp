#include <MessageTestCore.hpp>

TEST_F(MessageFixture, isMessageCorrectCreatedFromFullMessageInRow)
{
    EXPECT_TRUE(true);
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromParameters)
{
    Message readMessage("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    Message inviterMessage("[1][2019-03-21 08:41:30][mnurzyns][test inviter message]");
    Message recipientMessage("[2][2019-03-21 08:41:30][mnurzyns][test recipient message]");
    EXPECT_EQ(*expectedReadMessage, readMessage.messageToSave());
    EXPECT_EQ(*expectedInviterMessage, inviterMessage.messageToSave());
    EXPECT_EQ(*expectedRecipientMessage, recipientMessage.messageToSave());
}

TEST_F(MessageFixture, isTimeFromMessageCorrectReturned)
{
    Message readMessage(*expectedReadMessage);
    Message inviterMessage(*expectedInviterMessage);
    Message recipientMessage(*expectedRecipientMessage);

    std::string expectedTime = "2019-03-21 08:41:30";

    EXPECT_EQ(expectedTime, readMessage.getTime());
    EXPECT_EQ(expectedTime, inviterMessage.getTime());
    EXPECT_EQ(expectedTime, recipientMessage.getTime());
}

TEST_F(MessageFixture, isUsernameFromMessageCorrectReturned)
{
    Message readMessage(*expectedReadMessage);
    Message inviterMessage(*expectedInviterMessage);
    Message recipientMessage(*expectedRecipientMessage);

    std::string expectedUsername = "mnurzyns";

    EXPECT_EQ(expectedUsername, readMessage.getUsername());
    EXPECT_EQ(expectedUsername, inviterMessage.getUsername());
    EXPECT_EQ(expectedUsername, recipientMessage.getUsername());
}

TEST_F(MessageFixture, isContentFromMessageCorrectReturned)
{
    Message readMessage(*expectedReadMessage);
    Message inviterMessage(*expectedInviterMessage);
    Message recipientMessage(*expectedRecipientMessage);

    std::string expectedReadContent = "test read message";
    std::string expectedInviterContent = "test inviter message";
    std::string expectedRecipientContent = "test recipient message";

    EXPECT_EQ(expectedReadContent, readMessage.getContent());
    EXPECT_EQ(expectedInviterContent, inviterMessage.getContent());
    EXPECT_EQ(expectedRecipientContent, recipientMessage.getContent());
}
