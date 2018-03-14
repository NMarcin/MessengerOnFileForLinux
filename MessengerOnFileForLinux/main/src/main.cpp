#include <iostream>
#include <math.h>
#include <string>


#include <GlobalVariables.hpp>
#include "FileHandling.hpp"
#include "RegisterUser.hpp"
#include "SignIn.hpp"
#include "SignOut.hpp"
#include <LocalUser.hpp>
#include <ChatRequest.hpp>

#include <Logger.hpp>
#include <ClasslessLogger.hpp>
#include <LogSpace.hpp>

double squareRoot(const double a) {
    double b = sqrt(a);
    if(b != b)
    {
        return -1.0;
    }
    else
    {
        return sqrt(a);
    }
}

int main(int argc, char **argv)
{
    initSigusr1Action();

    int h;
    std::cin >> h;
    if (h==0)
        while (true)
        {
        }

    RegisterUser registerUser;
    registerUser.registerNewUser();

    std::cerr << "h";

    std::cout << "LOGOWANIE" << std::endl;
    SignIn signIn;
    signIn.signInUser();

    ChatRequest chat;
    chat.sendChatRequest("marcin1008");

    SignOut signOut;
    signOut.signOutUser();

    fileLog("Witamy w logerze!", LogSpace::main);

    return 0;
}
