#include <iostream>
#include <math.h>

#include "FileHandling.hpp"
#include "RegisterUser.hpp"
#include "SignIn.hpp"
#include "SignOut.hpp"
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

    fileLog("Witamy w logerze!", LogSpace::main);

    return 0;
}
