#include <thread>

#include <ChatRequestTestCore.hpp>
#include <SignIn.hpp>
#include <SignOut.hpp>
#include <RegisterUser.hpp>
#include <GlobalVariables.hpp>



ChatRequestFixture::ChatRequestFixture()
{
    waitForInvitation = std::thread(lookForInvitationGT);
}

void ChatRequestFixture::SetUp()
{
    isMessengerRunnigTest = true;
    std::istringstream stream("1\n1\n1");
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
    std::string command = "rm -r " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + "*" + user + "*";
    system(command.c_str());

}

ChatRequestFixture::~ChatRequestFixture()
{
    isMessengerRunnigTest = false;
    waitForInvitation.join();
    sleep(1);
}

int ChatRequestFixture::isMessengerRunnigTest = true;

void ChatRequestFixture::lookForInvitationGT()
{
    while (isMessengerRunnigTest)
    {
        auto invitationsFolderContent = FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS);
        if (0 == invitationsFolderContent->size())
        {
            sleep(1);
            continue;
        }
        for(auto invitation : *invitationsFolderContent)
        {
            std::string recipent;
            std::string inviter;
            bool getRecipentName = true;

            for (auto letter : invitation)
            {
                if (!getRecipentName)
                {
                    inviter += letter;
                }

                else if ('_' != letter)
                {
                    recipent += letter;
                }

                else if ( '_' == letter)
                {
                    getRecipentName = false;
                }

            }

            if (recipent == getenv("USER"))
            {
                ChatRequest chatRequest;
                chatRequest.answerForChatRequest(inviter);
            }
        }
    }
}

