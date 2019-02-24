// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>
#include <GlobalVariables.hpp>
#include <SignalHandling.hpp>
#include "ConsoleWindow.hpp"

#define ever (;;)

void Controler::controlUserAction()
{
    initscr();
    ConsoleWindow::displayMainWindow();


    log_.function("Controler::controlUserAction() started");

    for ever
    {
        std::signal(SIGWINCH, SignalHandling::NCoursesSignal::resizeHandlerInMainWindow);
        TerminalControl::isWaitingForInvitation = true;

        log_.debug("Controler::controlUserAction() Loop begin ");
        log_.debug(("Controler::controlUserAction() isWaitingForInvitation = " + std::to_string(TerminalControl::isWaitingForInvitation)).c_str());
        log_.debug(("Controler::controlUserAction() isInvitationExist = " + std::to_string(TerminalControl::isInvitationExist)).c_str());

        std::thread waitForInvitation(terminalControl_->lookForInvitation);
        std::shared_ptr<ChatInformation> chatInfo = std::make_shared<ChatInformation>();
        terminalControl_ = std::make_unique<TerminalControl>(ChatStatus::terminal, chatInfo);
        terminalControl_->waitingInTerminal();

        log_.debug("Controler::controlUserAction() waitingInTerminal finished");

        TerminalControl::isWaitingForInvitation = false;
        TerminalControl::isInvitationExist = false;
        waitForInvitation.join();

        log_.debug(("Controler::controlUserAction() isWaitingForInvitation = " + std::to_string(TerminalControl::isWaitingForInvitation)).c_str());
        log_.debug(("Controler::controlUserAction() isInvitationExist = " + std::to_string(TerminalControl::isInvitationExist)).c_str());

        if(not chatInfo->chatPath_.empty())
        {
            log_.info("Controler::controlUserAction() ConversationControl START()");
            conversationControl_ = std::make_unique<ConversationControl>(chatInfo);
            conversationControl_->conversation();
            conversationControl_->conversationEpilog();
            log_.info("Controler::controlUserAction() ConversationControl END()");
        }
    }
}
