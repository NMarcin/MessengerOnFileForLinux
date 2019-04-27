#pragma once
#include <csignal>
#include <stdlib.h>
#include <array>

#include "NcursesPrintToMainWindowOperationWrapper.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"

namespace
{
static constexpr int NUMBER_OF_HANLING_POSIX_SIGNALS = 5;
static constexpr std::array<int, NUMBER_OF_HANLING_POSIX_SIGNALS> posixSignalsCausingUnexpectedApplicationEndings{SIGINT,
                                                                                                                  SIGHUP,
                                                                                                                  SIGCONT,
                                                                                                                  SIGTERM,
                                                                                                                  0};
}//namespace

class SignalHandler
{
public:
    static void posixSignalHandlerInMainConsole(int signal);
    static void posixSignalHandlerInChatConsole(int signal);
    static void createPosixSignalsHandling(void(*handlingFunction)(int));
    static void terminalResizeHandlerInMainWindow(int);
    static void terminalResizeHandlerInRegistrationWindow(int);
    static void terminalResizeHandlerInSignInWindow(int);
    static void terminalResizeHandlerInChatWindow(int);

private:
    static NcursesPrintToMainWindowOperationWrapper _nCursesPrintOperationWrapper;
};

