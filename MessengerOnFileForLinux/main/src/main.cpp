#include <iostream>
#include <math.h>
#include <string>
#include <thread>
#include <chrono>

#include <GlobalVariables.hpp>
#include <FileHandling.hpp>
#include <RegisterUser.hpp>
#include <SignIn.hpp>
#include <SignOut.hpp>
#include <LocalUser.hpp>
#include <ChatRequest.hpp>
#include <Sender.hpp>
#include <ChatControl.hpp>

#include <Logger.hpp>
#include <ClasslessLogger.hpp>
#include <LogSpace.hpp>

void foo()
{
    std::cout << "Foo() opened by: "<< std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void mnurzyns()
{
    std::cout << "mnurzyns:\n\n";
    fileLog("Witamy w logerze!", LogSpace::main);
}

void mwozniak()
{
    FileInterface::Accesor::getRow("/home/messenger/TEST/test.txt", "dupa");

    std::cout << "ATOI: " << std::atoi("2marcin1006") << std::endl;

    std::thread waitForInvitation(lookForInvitation);

    std::cout << "REJETRACJA" << std::endl;
    RegisterUser registerUser;
    registerUser.registerNewUser();

    std::cout << "LOGOWANIE" << std::endl;
    SignIn signIn;
    signIn.signInUser();
    int i = 1;
    do
    {

        int j = 0;
        std::cout << "Wybierz opcje: ";
        std::cin >> j;

        switch (j) {
        case 1:
        {
            std::cout << " Kogo chcesz zaprosic ? ";
            std::string who;
            std::cin >> who;
            ChatControl control;
            control.conversationProlog(who, ChatRole::inviter);
        }
            break;

        case 2:
        {
            i = 0;
            isMessengerRunnig = false;
        }
            break;
        default:
            break;
        }
        sleep(1);

    }while(i);

    waitForInvitation.join();
    SignOut signOut;
    signOut.signOutUser();

}

enum class Run
{
    mnurzyns,
    mwozniak,
    both
};

int main(int argc, char **argv)
{
    //Run version = Run::mnurzyns;
    Run version = Run::mwozniak;

    if (Run::mnurzyns == version)
    {
        mnurzyns();
    }
    else if (Run::mwozniak == version)
    {
        mwozniak();
    }
    else if (Run::both == version)
    {
        mnurzyns();
        std::cout << std::endl << std::endl << std::endl;
        mwozniak();
    }


    return 0;
}
