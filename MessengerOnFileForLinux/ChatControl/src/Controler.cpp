// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>
#include <GlobalVariables.hpp>
#include <SignalHandling.hpp>

#define ever (;;)

void Controler::controlUserAction()
{
    log_.function("Controler::controlUserAction()");
    std::thread waitForInvitation(terminalControl_->lookForInvitation);
    std::shared_ptr<ChatInformation> chatInfo = std::make_shared<ChatInformation>();
    for ever
    {

        log_.function("Controler::controlUserAction() Poczatek petli");
        terminalControl_ = std::make_unique<TerminalControl>(ChatStatus::terminal, chatInfo);

        terminalControl_->waitingInTerminal();

        log_.info("Controler::controlUserAction() TerminalControl end");
        log_.info(chatInfo->chatPath_);
        log_.info(chatInfo->messageFlag_);
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
