#include <SignalHandling.hpp>
#include <SignOut.hpp>
#include <ConversationControl.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include <ClasslessLogger.hpp>

#include <utility>
#include <cstring>

namespace SignalHandling
{
namespace
{
static bool isChatResourcesDealocated = false;

std::string getChatFolderName()
{
    auto fileNamesFormFolder = FileInterface::Accesor::getFilenamesFromFolder(ENVIRONMENT_PATH::TO_FOLDER::CHATS);
    if (fileNamesFormFolder)
    {
        for (const auto& x : *fileNamesFormFolder)
        {
            if (std::string::npos != x.find(getenv("USER")))
            {
                return x;
            }
        }
    }
    return "";
}

void closeMessegner()
{
    SignOut signOut;
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
}
}//namespace

void posixSignalHandlerInMainConsole(int signal)
{
    const std::string log = "Signal nr=" + std::to_string(signal) + "handled in main console";
    fileLog(log.c_str(), LogSpace::Common);
    if (not isChatResourcesDealocated)
    {
        isChatResourcesDealocated = true;
        fileLog("Start of remove chat resources", LogSpace::Common);
        closeMessegner();
    }
}

void posixSignalHandlerInChatConsole(int signal)
{
    const std::string log = "Signal nr=" + std::to_string(signal) + "handled in chat console";
    fileLog(log.c_str(), LogSpace::Common);

    if (not isChatResourcesDealocated)
    {
        isChatResourcesDealocated = true;
        fileLog("Start of remove chat resources", LogSpace::Common);
        std::string chatFolderName = getChatFolderName();
        if (FileInterface::Managment::isFileExist(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END"))
        {
            std::string command = "rm -rf " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName;
            system(command.c_str());
            closeMessegner();
        }
        else
        {
            FileInterface::Managment::createFile(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END");
            closeMessegner();
        }
    }
}

void createPosixSignalsHandling(void(*handlingFunction)(int))
{
    for (const auto signal : SignalHandling::signalsCausingUnexpectedApplicationEndings)
    {
        std::signal(signal, handlingFunction);
    }
}
}//SignalHandling
