#pragma once

#include <unistd.h>

#include <ChatControl.hpp>

namespace ENVIRONMENT_PATH
{
namespace TO_FILE
{
static const std::string REGISTERED= "/home/messenger/configuration/REGISTERED";
static const std::string LOGGED = "/home/messenger/configuration/LOGGED";
}

namespace TO_FOLDER
{
static const std::string HOME = getenv("HOME");
static const std::string USER = HOME + "/messenger/";
static const std::string CHATS = "/home/messenger/chats/";
static const std::string INVITATIONS = "/home/messenger/invitations/";
static const std::string INSTALL = "/home/messenger/installation/";

static const std::string TEST = "/home/messenger/TEST/";
}
}//ENVIRONMENT_PATH

namespace FileStructure {
namespace LoggedFile
{
    static constexpr int username = 0;
    static constexpr int status = 1;
}
namespace RegisteredFile
{
static constexpr int username = 0;
static constexpr int password = 1;
static constexpr int date = 2;
}
}//FileStructure

namespace UserStatus
{
static const std::string activeStatus = "0";
static const std::string bussyStatus = "1";
}



/** To do jakiegos inita ***********************************/

static int isMessengerRunnig = true;


static void lookForInvitation()
{
    while (isMessengerRunnig)
    {
        auto invitationsFolderContent = FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::INVITATIONS);
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


