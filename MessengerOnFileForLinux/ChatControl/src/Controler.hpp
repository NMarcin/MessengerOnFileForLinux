#pragma once
#include <memory>

#include <TerminalControl.hpp>
#include <ConversationControl.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>


class Controler
{
public:
    void controlUserAction();

private:
    std::unique_ptr<TerminalControl> terminalControl_;
    std::unique_ptr<ConversationControl> conversationControl_;

    Logger log_{LogSpace::ChatControl};
};
