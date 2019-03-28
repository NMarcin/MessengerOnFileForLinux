#include <PurgeMessageTestCore.hpp>
#include <regex>
#include <cstring>
#include <iostream>

TEST_F(PurgeMessageFixture, isPurgeMessageCorrectCreatedFromMessage)
{
    const PurgeMessage purgeMessage(*_message);
    EXPECT_EQ(*_expectedPurgeMessage, purgeMessage.messageToShow());
}

TEST_F(PurgeMessageFixture, isPurgeMessageCorrectCreatedFromDeafultCopyCtor)
{
    const PurgeMessage purgeMessage(*_message);
    ASSERT_EQ(*_expectedPurgeMessage, purgeMessage.messageToShow());

    PurgeMessage copiedPurgeMessage = purgeMessage;
    EXPECT_EQ(purgeMessage.messageToShow(), copiedPurgeMessage.messageToShow());
    EXPECT_EQ(*_expectedPurgeMessage, copiedPurgeMessage.messageToShow());
}

TEST_F(PurgeMessageFixture, isPurgeMessageCorrectCreatedFromDeafultMoveCtor)
{
    PurgeMessage purgeMessage(*_message);
    ASSERT_EQ(*_expectedPurgeMessage, purgeMessage.messageToShow());

    PurgeMessage movedPurgeMessage(std::move(purgeMessage));
    EXPECT_NE(purgeMessage.messageToShow(), movedPurgeMessage.messageToShow());
    EXPECT_EQ(*_expectedPurgeMessage, movedPurgeMessage.messageToShow());
}
