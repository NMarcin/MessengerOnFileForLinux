#pragma once

#include <TerminalCommand.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class HistoryDowloander : public TerminalCommand
{
public:
    bool doCommand() override;

    HistoryDowloander(std::string command, std::string chatFileWithPath);
    ~HistoryDowloander() = default;;

private:
    std::string chatFileWithPath_;

    Logger log_ {LogSpace::TerminalFunctionality};
};
