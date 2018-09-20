#pragma once

#include <TerminalFunctionality.hpp>
#include <functional>
#include <TerminalControl.hpp>

class InviteSender : public TerminalCommand
{
public:
    bool doCommand(){return true;}
    bool doCommand(TerminalControl* x);

    InviteSender(std::string command);
    ~InviteSender();

private:
    std::string command_;
};

