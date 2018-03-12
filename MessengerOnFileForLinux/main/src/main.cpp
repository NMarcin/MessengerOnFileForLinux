#include <iostream>
#include <math.h>

#include "FileHandling.hpp"
#include "RegisterUser.hpp"
#include "SignIn.hpp"
#include "SignOut.hpp"
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
    std::cout << "mwozniak:\n\n";
    /*
    createFile("plik.txt", "../");
    createFile("tmp.txt");
    addRow("plik.txt","costamcostam");
    addRow("plik.txt","costamcostam", "../");
    addRow("tmp.txt","wwwwwmcostam");
    */
    RegisterUser registerUser;
    registerUser.registerNewUser();
    std::cout << "LOGOWANIE" << std::endl;
    SignIn signIn;
    signIn.signInUser();
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
    Run version = Run::mnurzyns;

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
