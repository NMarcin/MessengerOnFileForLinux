#include <iostream>
#include <math.h>

#include "FileHandling.hpp"
#include "RegisterUser.hpp"
#include "SignIn.hpp"
#include "SignOut.hpp"
#include <Logger.hpp>

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


double foo()
{
    int* x = new int(10);
    x[10] = 0;
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



    return 0;
}
