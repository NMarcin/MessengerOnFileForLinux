#include <PurgeMessageTestCore.hpp>
#include <regex>
#include <cstring>
#include <iostream>

TEST_F(PurgeMessageFixture, isPurgeMessageCorrectCreatedFromMessage)
{
    const PurgeMessage purgeMessage(*message);
    EXPECT_EQ(*expectedPurgeMessage, purgeMessage.messageToShow());
}

TEST_F(PurgeMessageFixture, isPurgeMessageCorrectCreatedFromDeafultCopyCtor)
{
    const PurgeMessage purgeMessage(*message);
    ASSERT_EQ(*expectedPurgeMessage, purgeMessage.messageToShow());

    PurgeMessage copiedPurgeMessage = purgeMessage;
    EXPECT_EQ(purgeMessage.messageToShow(), copiedPurgeMessage.messageToShow());
    EXPECT_EQ(*expectedPurgeMessage, copiedPurgeMessage.messageToShow());
}

TEST_F(PurgeMessageFixture, isPurgeMessageCorrectCreatedFromDeafultMoveCtor)
{
    PurgeMessage purgeMessage(*message);
    ASSERT_EQ(*expectedPurgeMessage, purgeMessage.messageToShow());

    PurgeMessage movedPurgeMessage(std::move(purgeMessage));
    EXPECT_NE(purgeMessage.messageToShow(), movedPurgeMessage.messageToShow());
    EXPECT_EQ(*expectedPurgeMessage, movedPurgeMessage.messageToShow());
}
