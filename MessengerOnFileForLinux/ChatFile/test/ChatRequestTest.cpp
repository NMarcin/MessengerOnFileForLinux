#include <ChatRequestTest.hpp>
#include <RegisterUser.hpp>
#include <SignIn.hpp>
#include <SignOut.hpp>

ChatRequestFixture::ChatRequestFixture()
{
    //NOOP
}

void ChatRequestFixture::SetUp()
{
    RegisterUser registerUser;
    registerUser.registerNewUser();
    SignIn signIn;
    signIn.signInUser();
}

void ChatRequestFixture::TearDown()
{
    SignOut signOut;
    signOut.signOutUser();
}

ChatRequestFixture::~ChatRequestFixture()
{
    //NOOP
}
