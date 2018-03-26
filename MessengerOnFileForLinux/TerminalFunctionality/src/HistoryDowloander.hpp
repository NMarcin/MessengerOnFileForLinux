#pragma once

#include <TerminalCommand.hpp>

class HistoryDowloander : public TerminalCommand
{
public:
    bool doCommand() override;

    HistoryDowloander(std::string command);
    ~HistoryDowloander();

private:
};
