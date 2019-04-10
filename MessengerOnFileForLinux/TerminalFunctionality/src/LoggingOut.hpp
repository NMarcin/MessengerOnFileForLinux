#pragma once

#include<TerminalCommand.hpp>
#include <Logger.hpp>
#include <LogSpace.hpp>

class LoggingOut : public TerminalCommand
{
public:
    bool doCommand() const override;

    LoggingOut(std::string command);
    ~LoggingOut() = default;

    LoggingOut(LoggingOut &&) = delete;
    LoggingOut operator=(LoggingOut &&) = delete;
    LoggingOut(const LoggingOut &) = delete;
    LoggingOut operator=(const LoggingOut &) = delete;

private:
    Logger _log {LogSpace::TerminalFunctionality};
};
