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

    EXPECT_TRUE(std::regex_match(strReadMessage, matcherRead, regexReadMessage));
    EXPECT_TRUE(std::regex_match(strInviterMessage, matcherInviter, regexInviterMessage));
    EXPECT_TRUE(std::regex_match(strRecipientMessage, matcherRecipient, regexRecipientMessage));
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromFullMessageInRow)
{
    comparingExpectedMessageWithCreatedFromFullString(*_expectedReadMessage);
    comparingExpectedMessageWithCreatedFromFullString(*_expectedInviterMessage);
    comparingExpectedMessageWithCreatedFromFullString(*_expectedRecipientMessage);
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromDeafultCopyCtor)
{
    const Message readMessage("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    ASSERT_EQ(*_expectedReadMessage, readMessage.messageToSave());

    Message copiedMessage = readMessage;
    EXPECT_EQ(readMessage.messageToSave(), copiedMessage.messageToSave());
    EXPECT_EQ(*_expectedReadMessage, copiedMessage.messageToSave());
}

TEST_F(MessageFixture, isMessageCorrectCreatedFromDeafultMoveCtor)
{
    Message readMessage("[0][2019-03-21 08:41:30][mnurzyns][test read message]");
    ASSERT_EQ(*_expectedReadMessage, readMessage.messageToSave());

    Message movedMessage(std::move(readMessage));
    EXPECT_NE(readMessage.messageToSave(), movedMessage.messageToSave());
    EXPECT_EQ(*_expectedReadMessage, movedMessage.messageToSave());
}

TEST_F(MessageFixture, isTimeFromMessageCorrectReturned)
{
    comparingExpectedTimeWithTimeFromMessage(*_expectedReadMessage);
    comparingExpectedTimeWithTimeFromMessage(*_expectedInviterMessage);
    comparingExpectedTimeWithTimeFromMessage(*_expectedRecipientMessage);
}

TEST_F(MessageFixture, isUsernameFromMessageCorrectReturned)
{
    comparingExpectedUsernameWithUsernameFromMessage(*_expectedReadMessage);
    comparingExpectedUsernameWithUsernameFromMessage(*_expectedInviterMessage);
    comparingExpectedUsernameWithUsernameFromMessage(*_expectedRecipientMessage);
}

TEST_F(MessageFixture, isContentFromMessageCorrectReturned)
{
    comparingExpectedContentWithContentFromMessage(*_expectedReadMessage, "read");
    comparingExpectedContentWithContentFromMessage(*_expectedInviterMessage, "inviter");
    comparingExpectedContentWithContentFromMessage(*_expectedRecipientMessage, "recipient");
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
