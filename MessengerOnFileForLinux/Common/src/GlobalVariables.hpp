#pragma once

namespace
{
static const std::string path = "/var/tmp/";
}//namespace

static const std::string LOCAL_USER = getenv("USER");

namespace ENVIRONMENT_PATH
{
namespace TO_FILE
{
static const std::string REGISTERED= path + "messenger/configuration/REGISTERED";
static const std::string LOGGED = path + "messenger/configuration/LOGGED";
}//TO_FILE

namespace TO_FOLDER
{
static const std::string HOME = getenv("HOME");
static const std::string USER = HOME + "/messenger/";
static const std::string CHATS = path + "messenger/chats/";
static const std::string INVITATIONS = path + "messenger/invitations/";
static const std::string INSTALL = path + "messenger/installation/";

static const std::string TEST = path + "messenger/TEST/";
}//TO FOLDER
}//ENVIRONMENT_PATH

namespace FileStructure {
namespace LoggedFile
{
    static constexpr int username = 0;
    static constexpr int status = 1;
}//LoggedFile

namespace RegisteredFile
{
static constexpr int username = 0;
static constexpr int password = 1;
static constexpr int date = 2;
}//RegisteredFile

namespace MessageFile
{
static constexpr int flag = 0;
static constexpr int date = 1;
static constexpr int username = 2;
static constexpr int message = 3;
}//MessageFile

} //FileStructure

namespace UserStatus
{
static const std::string activeStatus = "0";
static const std::string bussyStatus = "1";
}//UserStatus

namespace MessageFlag
{
    static const std::string readMessage = "0";
    static const std::string inviterMessage = "1";
    static const std::string recipientMessage = "2";
}//MessageFlag





