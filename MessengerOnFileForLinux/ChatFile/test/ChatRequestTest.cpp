#include <ChatRequestTestCore.hpp>

/*
TEST_F(ChatRequestFixture, inviteInactiveUser)
{
    FileInterface::Modification::removeRow(ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE, user);

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, inviteBussyUser)
{
    FileInterface::Modification::updateRowField(ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE, user,
                                                FileStructure::FieldValue::userBussyStatus,
                                                FileStructure::FileField::statusFieldInLoggedFile);

    EXPECT_FALSE(chatRequest.sendChatRequest(user));

}

TEST_F(ChatRequestFixture, inviteActiveUserWithDissacceptResponse_1)
{
    std::istringstream stream("n");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, inviteActiveUserWithDissacceptResponse_2)
{
    std::istringstream stream("no");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}*/
/*
TEST_F(ChatRequestFixture, inviteActiveUserWithAcceptResponse_1)
{
    std::istringstream stream("y");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user));

}

TEST_F(ChatRequestFixture, inviteActiveUserWithAcceptResponse_2)
{
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream stream("yes");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user));
    std::cin.rdbuf(orig);
}

TEST_F(ChatRequestFixture, isUserActiveAfterChatStart)
{
    std::istringstream stream("y");
    std::cin.rdbuf(stream.rdbuf());
    EXPECT_TRUE(chatRequest.sendChatRequest(user));
    //sleep(1);
    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, isToLowerWorking)
{
    std::istringstream stream("YES");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user));
}
*//*
TEST_F(ChatRequestFixture, inviteActiveUserWithUndefinedResponse)
{
    std::istringstream stream("somethigElseThanYesOrNo");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}*/
