// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>

#define ever (;;)

void Controler::controlUserAction()
{
    log_.function("Controler::controlUserAction()");
    for ever
    {
        log_.info("Controler::controlUserAction() TerminalControl start");
        terminalControl_ = std::make_unique<TerminalControl>(ChatStatus::terminal);
        terminalControl_->waitingInTerminal();
        log_.info("Controler::controlUserAction() TerminalControl end, ConversationControl start");
        //conversationControl_ = std::make_unique<ConversationControl>();
        //conversationControl_->conversation(); //tu trzeba przekazac jakos chatFilePath i messagEFlag
        conversationControl_->conversationEpilog();
        log_.info("Controler::controlUserAction() TerminalControl end");
    }
}
