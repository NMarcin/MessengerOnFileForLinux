#pragma once

#include "TerminalCommand.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"

class HistoryDowloander : public TerminalCommand
{
public:
    bool doCommand() override;

    HistoryDowloander(std::string command, std::string chatFileWithPath);
    ~HistoryDowloander() = default;

    HistoryDowloander(HistoryDowloander &&) = delete;
    HistoryDowloander operator=(HistoryDowloander &&) = delete;
    HistoryDowloander(const HistoryDowloander &) = delete;
    HistoryDowloander operator=(const HistoryDowloander &) = delete;

private:
    std::string _chatFileWithPath;

    Logger _log {LogSpace::TerminalFunctionality};
};
