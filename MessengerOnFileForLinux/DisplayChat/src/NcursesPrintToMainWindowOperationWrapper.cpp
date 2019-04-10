#include "NcursesPrintToMainWindowOperationWrapper.hpp"

#include <ncurses.h>
#include <chrono>
#include <thread>

void NcursesPrintToMainWindowOperationWrapper::printInformationIntoMainWindow(const std::string& informationToPrint) const
{
    printw(informationToPrint.c_str());
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void NcursesPrintToMainWindowOperationWrapper::printMainWindow() const
{
    printBasesInformationIntoMainWindow({informationToDisplayInMainWindow,
                                         getenv("USER")});

    printw(">>");
    move(2,3);
    refresh();
}

void NcursesPrintToMainWindowOperationWrapper::printRegistrationWindow() const
{
    printBasesInformationIntoMainWindow({hello,
                                         getenv("USER"),
                                         informationToDisplayDuringRegistration});;

    printInformationAboutEnteringPassword();
}

void NcursesPrintToMainWindowOperationWrapper::printSignInWindow() const
{
    printBasesInformationIntoMainWindow({hello,
                                         getenv("USER"),
                                         informationToDisplayDuringSignIn});

    printInformationAboutEnteringPassword();
}

void NcursesPrintToMainWindowOperationWrapper::printBasesInformationIntoMainWindow(const std::initializer_list<const char*>&& informationsToDisplay) const
{
    clear();
    move(0,0);

    for (const auto& information : informationsToDisplay)
    {
        printw(information);
    }

    move(2,0);
}

void NcursesPrintToMainWindowOperationWrapper::printInformationAboutEnteringPassword() const
{
    printw(enterPassword);
    refresh();
}
