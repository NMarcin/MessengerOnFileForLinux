#pragma once
// DODAC DO CMAKOW TEST
#include <memory>

#include <TerminalControl.hpp>
#include <ConversationControl.hpp>

class Controler
{
public:
    void controlUserAction();

private:
    std::unique_ptr<TerminalControl> terminalControl_;
    std::unique_ptr<ConversationControl> conversationControl_;
};
