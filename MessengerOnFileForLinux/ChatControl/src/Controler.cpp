// dodac do cmakow

#include <Controler.hpp>
#include <TerminalControl.hpp>

#define ever (;;)

void Controler::controlUserAction()
{
    for ever
    {
        terminalControl_ = std::make_unique<TerminalControl>();
        terminalControl_->waitingInTerminal();

        //conversationControl_ = std::make_unique<ConversationControl>();
        //conversationControl_->conversation(); //tu trzeba przekazac jakos chatFilePath i messagEFlag
        conversationControl_->conversationEpilog();
    }
}

// w mainie bedzie taka kolejnosc:
// logowanie z ewentualna rejestracja
// controlUserAction
// zakonczenie chatu
