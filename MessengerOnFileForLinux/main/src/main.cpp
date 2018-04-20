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

void mnurzyns()
{
    std::cout << "mnurzyns:\n\n";
    fileLog("Witamy w logerze!", LogSpace::main);
}

void mwozniak()
{
    std::string user = getenv("USER");
    std::thread waitForInvitation(lookForInvitation);
    std::cout <<"..........:::::::::Welcome " + user + "::::::::::.........." << std::endl;



    int option = 0;

    bool isSignInSuccesfully = false;
    while (!isSignInSuccesfully)
    {
        std::cout << "Choose option: " << std::endl;
        std::cout << "(1) Register" << std::endl;
        std::cout << "(2) SignIn" << std::endl;
        std::cout << ">> ";
        std::cin >> option;
        std::cout << std::endl;

        if (1 == option)
        {
            RegisterUser registerUser;
            SignIn signIn;
            registerUser.registerNewUser();
            std::cout << "___Sign In___" << std::endl;
            if (signIn.signInUser())
            {
                isSignInSuccesfully = true;
            }
        }
        else if (2 == option)
        {
            SignIn signIn;
            if (signIn.signInUser())
            {
                isSignInSuccesfully = true;
            }
        }
    }

    while (true)
    {
        std::cout << "Choose option: " << std::endl;
        std::cout << "(1) Invite user" << std::endl;
        std::cout << ">> ";
        std::cin.clear();
        std::cin.sync();
        std::cin >> std::ws;
        std::cin >> option;
        std::cout <<"." << option <<"." << std::endl;
        std::cout << std::endl;

        if (1 == option)
        {
            ChatControl control;
            std::cout << " who do you want to invite? Invite ";
            std::string who;
            std::cin >> who;
            control.conversationProlog(who, ChatRole::inviter);
        }

        else
        {
            while (true)
            {}
        }
    }



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
