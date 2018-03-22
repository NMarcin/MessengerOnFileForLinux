#include <iostream>
#include <math.h>
#include <string>


#include <GlobalVariables.hpp>
#include <FileHandling.hpp>
#include <RegisterUser.hpp>
#include <SignIn.hpp>
#include <SignOut.hpp>
#include <LocalUser.hpp>
#include <ChatRequest.hpp>
#include <Sender.hpp>

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
    std::string fileName("125Dupaasd23");
    auto it = fileName.begin();
    while (isdigit(*it))
    {
        --it;

    }
    std::string tmp(it, fileName.end());
    std::cout << tmp;

    std::cout << *FileInterface::Accesor::getFolderName("/home/marcin/plik/dupa.txt") << std::endl;


  initSigusr1Action();

  int h;
  std::cin >> h;
  if (h==0)
      while (true)
      {
      }
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

    ChatRequest chat;
    chat.sendChatRequest("marcin1008");

    //Sender sender;
    //sender.sendMessage("marcin1008");

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
