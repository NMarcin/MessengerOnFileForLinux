#pragma once
#include <string>
#include <signal.h> //to wszystko ponizej potrzebne do initu dzialania sygnalu
#include <unistd.h>
#include <stdio.h>
#include <sys/sysctl.h>
#include <ctime>
#include <string.h>
#include <iostream>

#include <ChatControl.hpp>
#include <ChatRequest.hpp>



namespace ENVIRONMENT_PATH
{
    namespace TO_FILE
    {
        static const std::string REGISTERED_FILE= "/home/messenger/configuration/REGISTERED.txt";
        static const std::string LOGGED_FILE = "/home/messenger/configuration/LOGGED.txt";
    }

    namespace TO_FOLDER
    {
        static const std::string HOME_FOLDER = getenv("HOME");
        static const std::string USER_FOLDER = HOME_FOLDER + "/messenger/";
        static const std::string CHATS_FOLDER = "/home/messenger/chats/";
        static const std::string INSTALL_FOLDER = "/home/messenger/installation/";

        static const std::string TEST_FOLDER = "/home/messenger/TEST/";
    }
}

namespace FileStructure {

    namespace FileField //TODO mwozniak rozbic na mniejsze (namespace RegisteredFile i LoggedFile)
    {
        static constexpr int usernameFieldInLoggedFile = 0;
        static constexpr int statusFieldInLoggedFile = 1;
        static constexpr int pidFieldInLoggedFile = 2;
        static constexpr int usernameFieldInRegisteredFile = 0;
        static constexpr int passwordFieldInRegisteredFile = 1;
        static constexpr int dateTimeFieldInRegisteredFile = 2;
    }

    namespace FieldValue // TODO do wyjebania -> trzymac gdzie indziej
    {
        static const std::string userActiveStatus = "0";
        static const std::string userBussyStatus = "1";
    }
}


/** To do jakiegos inita ***********************************/


static void sigusr1Handler(int sig_num, siginfo_t *info, void *context)
{
    if (NULL == info)
    {
        std::cerr << "WARNING: info = NULL" << std::endl;
    }
    std::string command = "ps axo user:20,command,pid | grep signal.sh";
    std::string output = ConsolControl::getStdoutFromCommand(command);
    std::string username;
    for (auto& x: output)
    {
        if (x == ' ')
            break;
        else
            username += x;
    }
    std::cout << "Sygnal przyszedl od: " << username << std::endl;
    ChatControl chatControl;
    chatControl.startConversation(username, ChatRole::recipient);
    //TODO mwozniak potestowac. Wczesniej na chatRequest dzialolo dobrze
}

static void initSigusr1Action()
{
    sigset_t iset;
    struct sigaction act;
    sigemptyset(&iset);

    act.sa_sigaction = sigusr1Handler;
    act.sa_mask = iset;
    act.sa_flags |= SA_SIGINFO;

    //memset(&act, 0, sizeof(act));

    sigaction(SIGUSR1, &act, NULL);

}

/** **********************************************************/
