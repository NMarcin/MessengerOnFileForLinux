#include "ChatRequestTestCore.hpp"

#include <SignIn.hpp>
#include <SignOut.hpp>
#include <RegisterUser.hpp>


ChatRequestFixture::ChatRequestFixture()
{
    //NOOP
}

void ChatRequestFixture::SetUp()
{
    initSigusr1Action();

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
