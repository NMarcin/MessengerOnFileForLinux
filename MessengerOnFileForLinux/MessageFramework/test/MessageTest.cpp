#include <MessageTestCore.hpp>
#include <regex>
#include <cstring>
#include <iostream>

TEST_F(MessageFixture, isMessageCorrectCreatedFromParameters)
{
         const std::regex regexReadMessage("\\[0]\\[20([0-9]{2})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})]\\[mnurzyns]\\[test read message]");
      const std::regex regexInviterMessage("\\[1]\\[20([0-9]{2})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})]\\[mnurzyns]\\[test inviter message]");
    const std::regex regexRecipientMessage("\\[2]\\[20([0-9]{2})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2})]\\[mnurzyns]\\[test recipient message]");

    std::smatch matcherRead;
    std::smatch matcherInviter;
    std::smatch matcherRecipient;

    Message readMessage("0", "mnurzyns", "test read message");
    Message inviterMessage("1", "mnurzyns", "test inviter message");
    Message recipientMessage("2", "mnurzyns", "test recipient message");

    const std::string strReadMessage = readMessage.messageToSave();
    const std::string strInviterMessage = inviterMessage.messageToSave();
    const std::string strRecipientMessage = recipientMessage.messageToSave();

    std::cout << strReadMessage << std::endl;
    std::cout << strInviterMessage << std::endl;
    std::cout << strRecipientMessage << std::endl;

    EXPECT_TRUE(std::regex_match(strReadMessage, matcherRead, regexReadMessage));
    EXPECT_TRUE(std::regex_match(strInviterMessage, matcherInviter, regexInviterMessage));
    EXPECT_TRUE(std::regex_match(strRecipientMessage, matcherRecipient, regexRecipientMessage));
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromFullMessageInRow)
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


TEST_F(MessageFixture, isIncorrectedMessageFlagDoesNotProvideErrors)
{
    const Message message("[p][2019-03-21 08:41:30][mnurzyns][test message]");

    EXPECT_EQ("[p][2019-03-21 08:41:30][mnurzyns][test message]", message.messageToSave());
}

TEST_F(MessageFixture, isIncorrectedContentDoesNotProvideErrors)
{
    const Message message("[0][2019-03-21 08:41:30][mnurzyns][//end]");

    EXPECT_EQ("//end", message.getContent());
}
