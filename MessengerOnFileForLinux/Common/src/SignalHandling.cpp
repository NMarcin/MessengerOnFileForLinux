#include <SignalHandling.hpp>
#include <SignOut.hpp>
#include <ConversationControl.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <LocalUser.hpp>
#include "ConsoleWindow.hpp"
#include "ChatWindow.hpp"

#include <utility>
#include <cstring>
#include <ncurses.h>


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

namespace NCoursesSignal
{
void resizeHandlerInMainWindow(int signal)
{
    fileLog("Console resize handled in main window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ConsoleWindow::displayMainWindow();
}

void resizeHandlerInRegistrationWindow(int signal)
{
    fileLog("Console resize handled in registration window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ConsoleWindow::displayRegistrationWindow();
}

void resizeHandlerInSignInWindow(int signal)
{
    fileLog("Console resize handled in sign window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    ConsoleWindow::displaySignInWindow();
}

void resizeHandlerInChatWindow(int signal)
{
    /*
     * Po resizie czyszczone jest okno, i wpadaja dwa puste stringi jak sie chce cos napisac.
     * Ale wyswietlane sa tylko u nadawcy. U odbiorcy dopiero pojawia sie kolejna wiadmosc.
     * W glownej petli dalej cos nie bangla do konca
     */

    fileLog("Console resize handled in chat window", LogSpace::Common);
    endwin();
    refresh();
    clear();
    //ChatWindow::deleteDisplayMesageWindow();
    //ChatWindow::deleteEnterMesageWindow();
    ChatWindow::displayChatWindows();
    ChatWindow::displayEnterMessageWindow();
    ChatWindow::displayDisplayMessageWindow("");
}

}//ResizeWindow
}//SignalHandling
