// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>
#include <GlobalVariables.hpp>
#include <SignalHandling.hpp>

#define ever (;;)

void Controler::controlUserAction()
{
    log_.function("Controler::controlUserAction()");
    std::shared_ptr<ChatInformation> chatInfo = std::make_shared<ChatInformation>();

    for ever
    {
        std::thread waitForInvitation(terminalControl_->lookForInvitation);


        terminalControl_ = std::make_unique<TerminalControl>(ChatStatus::terminal, chatInfo);
        terminalControl_->waitingInTerminal();
        TerminalControl::isWaitingForInvitation = false;
        waitForInvitation.join();
        if(not chatInfo->chatPath_.empty())
        {
            log_.info("Controler::controlUserAction() ConversationControl start end");
            conversationControl_ = std::make_unique<ConversationControl>(chatInfo);
            conversationControl_->conversation();

            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            conversationControl_->conversationEpilog();
        }


    }

}
