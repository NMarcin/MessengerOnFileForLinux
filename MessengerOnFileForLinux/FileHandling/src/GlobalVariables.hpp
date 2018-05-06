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
static const std::string REGISTERED_FILE= "/home/messenger/configuration/REGISTERED";
static const std::string LOGGED_FILE = "/home/messenger/configuration/LOGGED";
}

namespace TO_FOLDER
{
static const std::string HOME_FOLDER = getenv("HOME");
static const std::string USER_FOLDER = HOME_FOLDER + "/messenger/";
static const std::string CHATS_FOLDER = "/home/messenger/chats/";
static const std::string INVITATIONS_FOLDER = "/home/messenger/invitations/";
static const std::string INSTALL_FOLDER = "/home/messenger/installation/";

static const std::string TEST_FOLDER = "/home/messenger/TEST/";
}
}

namespace FileStructure {

namespace FileField //TODO mwozniak rozbic na mniejsze (namespace RegisteredFile i LoggedFile)
{
static constexpr int usernameFieldInLoggedFile = 0;
static constexpr int statusFieldInLoggedFile = 1;
//static constexpr int pidFieldInLoggedFile = 2;
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

static int isMessengerRunnig = true;


static void lookForInvitation()
{
    while (isMessengerRunnig)
    {
        auto invitationsFolderContent = FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS_FOLDER);
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
                ChatControl chatControl;
                chatControl.conversationProlog(inviter, ChatRole::recipient);
            }
        }
        sleep(1);
    }
}

/** **********************************************************/
