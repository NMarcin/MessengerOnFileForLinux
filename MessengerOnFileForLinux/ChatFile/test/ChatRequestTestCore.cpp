#include "ChatRequestTestCore.hpp"

#include <SignIn.hpp>
#include <SignOut.hpp>
#include <RegisterUser.hpp>


ChatRequestFixture::ChatRequestFixture()
{
    //NOOP
    initSigusr1Action();
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

void ChatRequestFixture::testSigusr1Handler(int sig_num, siginfo_t *info, void *context)
{
    if (NULL == info)
    {
        std::cerr << "WARNING: info = NULL" << std::endl;
    }
    ChatRequest chatRequest;
    chatRequest.answerForChatRequest(info -> si_pid);
}

void ChatRequestFixture::initSigusr1Action()
{
    sigset_t iset;
    struct sigaction act = {0};
    sigemptyset(&iset);
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = testSigusr1Handler;
    act.sa_mask = iset;
    act.sa_flags |= SA_SIGINFO;

    sigaction(SIGUSR1, &act, NULL);

}
