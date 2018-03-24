#include <ChatRequestTest.hpp>

#include <SignIn.hpp>
#include <SignOut.hpp>
#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

ChatRequestFixture::ChatRequestFixture()
{
    //NOOP
}

void ChatRequestFixture::SetUp()
{
    std::istringstream stream("3\n3\n3");
    std::cin.rdbuf(stream.rdbuf());
    RegisterUser registerUser;
    registerUser.registerNewUser();

    SignIn signIn;
    signIn.signInUser();
}

void ChatRequestFixture::TearDown()
{
    SignOut signOut;
    signOut.signOutUser();
    //TODO usunac jak bedzie napisane konczenie rozmowy
    std::string command = "rm -r " + ENIVRONMENT_PATH::PATH_TO_FOLDER::CHATS_FOLDER + "*" + user + "*";
    system(command.c_str());
}

ChatRequestFixture::~ChatRequestFixture()
{
    //NOOP
}

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

TEST_F(ChatRequestFixture, inviteActiveUserWithAcceptResponse_1)
{
    initSigusr1Action();
    std::istringstream stream("y");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, inviteActiveUserWithAcceptResponse_2)
{
    initSigusr1Action();
    std::istringstream stream("yes");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, inviteActiveUserWithDissacceptResponse_1)
{
    initSigusr1Action();
    std::istringstream stream("n");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, inviteActiveUserWithDissacceptResponse_2)
{
    initSigusr1Action();
    std::istringstream stream("no");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, isUserActiveAfterChatStart)
{
    initSigusr1Action();
    std::istringstream stream("y");
    std::cin.rdbuf(stream.rdbuf());
    chatRequest.sendChatRequest(user);

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, isToLowerWorking)
{
    initSigusr1Action();
    std::istringstream stream("YES");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(chatRequest.sendChatRequest(user));
}

TEST_F(ChatRequestFixture, inviteActiveUserWithUndefinedResponse)
{
    initSigusr1Action();
    std::istringstream stream("somethigElseThanYesOrNo");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(chatRequest.sendChatRequest(user));
}
