#include <SignalHandling.hpp>
#include <SignOut.hpp>
#include <ConversationControl.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>

#include <utility>
#include <cstring>


namespace SignalHandling
{

namespace
{
volatile std::sig_atomic_t signalStatus;
}

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

void sigintHandlerInMainConsole(int signal)
{
    fileLog("SIGINT handled in main console", LogSpace::Common);
    signalStatus = signal;
    SignOut signOut;
    signOut.signOutUser();
    exit (EXIT_SUCCESS);
}

void sigintHandlerInChatConsole(int signal)
{
    fileLog("SIGINT handled in chat console", LogSpace::Common);
    signalStatus = signal;
    std::string chatFolderName = getChatFolderName();
    fileLog(chatFolderName.c_str(), LogSpace::Common);

    if (FileInterface::Managment::isFileExist(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END"))
    {
        std::string command = "rm -rf " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName;
        system(command.c_str());
        SignOut signOut;
        signOut.signOutUser();
        exit (EXIT_SUCCESS);
    }
    else
    {
        FileInterface::Managment::createFile(ENVIRONMENT_PATH::TO_FOLDER::CHATS + chatFolderName + "/END");
        SignOut signOut;
        signOut.signOutUser();
        exit (EXIT_SUCCESS);
    }
}
}//SignalHandling
