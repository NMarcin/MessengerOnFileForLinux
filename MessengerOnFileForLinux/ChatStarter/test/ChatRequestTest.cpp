#include <ChatRequestTestCore.hpp>


TEST_F(ChatRequestFixture, inviteInactiveUser)
{
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE, user);

    EXPECT_TRUE(chatRequest.sendChatRequest(user).empty());
}

TEST_F(ChatRequestFixture, inviteBussyUser)
{
    FileInterface::Modification::updateRowField(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE, user,
                                                FileStructure::FieldValue::userBussyStatus,
                                                FileStructure::FileField::statusFieldInLoggedFile);

    EXPECT_TRUE(chatRequest.sendChatRequest(user).empty());

}

TEST_F(ChatRequestFixture, inviteActiveUserWithDissacceptResponse_1)
{
    std::istringstream stream("n");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user).empty());
}

TEST_F(ChatRequestFixture, inviteActiveUserWithDissacceptResponse_2)
{
    std::istringstream stream("no");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user).empty());
}

/*
 * Testujemy zapraszjac siebie, ale nie mozemy tego zrobic bo widzimi sami siebie
 * jako zajetego usera
 *
TEST_F(ChatRequestFixture, inviteActiveUserWithAcceptResponse_1)
{
    std::istringstream stream("y");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_EQ(chatRequest.sendChatRequest(user), pathToChatfile);
}


TEST_F(ChatRequestFixture, inviteActiveUserWithAcceptResponse_2)
{
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream stream("yes");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_EQ(chatRequest.sendChatRequest(user), pathToChatfile);
}

TEST_F(ChatRequestFixture, isUserActiveAfterChatStart)
{
    std::istringstream stream("y");
    std::cin.rdbuf(stream.rdbuf());
    EXPECT_EQ(chatRequest.sendChatRequest(user), pathToChatfile);
    EXPECT_NE(chatRequest.sendChatRequest(user), pathToChatfile);
}

TEST_F(ChatRequestFixture, isToLowerWorking)
{
    std::istringstream stream("YES");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_EQ(chatRequest.sendChatRequest(user), pathToChatfile);
}
*/
TEST_F(ChatRequestFixture, inviteActiveUserWithUndefinedResponse)
{
    std::istringstream stream("somethigElseThanYesOrNo");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_NE(chatRequest.sendChatRequest(user), pathToChatfile);
}

TEST_F(ChatRequestFixture, isGetChatFolderNameWorksCorrectly)
{
    system("mkdir 0mwoznia2_mnurzyns");
    system("mkdir 1mwoznia2_tkogut");
    system("mkdir 2mnurzyns_mwoznia2");
    std::string commandOutput = ConsolControl::getStdoutFromCommand("ls | grep mwoznia2_tkogut");
    commandOutput.pop_back(); //usuwanie znaku konca linii
                              //TODO mwoznia poprawic getStdoutFromCommand
    EXPECT_EQ(commandOutput, "1mwoznia2_tkogut");

    FileInterface::Managment::removeFile("0mwoznia2_mnurzyns");
    FileInterface::Managment::removeFile("1mwoznia2_tkogut");
    FileInterface::Managment::removeFile("2mnurzyns_mwoznia2");
}
