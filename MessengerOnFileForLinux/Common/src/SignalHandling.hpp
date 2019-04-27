#pragma once
#include <csignal>
#include <stdlib.h>
#include <array>

#include "NcursesPrintOperationWrapper.hpp"
#include "Logger.hpp"
#include "LogSpace.hpp"

namespace
{
static constexpr int NUMBER_OF_HANLING_POSIX_SIGNALS = 5;
}

static constexpr std::array<int, NUMBER_OF_HANLING_POSIX_SIGNALS> posixSignalsCausingUnexpectedApplicationEndings{SIGINT,
                                                                                                                  SIGHUP,
                                                                                                                  SIGCONT,
                                                                                                                  SIGTERM,
                                                                                                                  0};

class SignalHandler
{
public:
    SignalHandler(const NcursesPrintOperationWrapper& nCursesPrintOperationWrapper);

    static void posixSignalHandlerInMainConsole(int signal);
    static void posixSignalHandlerInChatConsole(int signal);
    static void createPosixSignalsHandling(void(*handlingFunction)(int));
    static void terminalResizeHandlerInMainWindow(int);
    static void terminalResizeHandlerInRegistrationWindow(int);
    static void terminalResizeHandlerInSignInWindow(int);
    static void terminalResizeHandlerInChatWindow(int);

private:
    const NcursesPrintOperationWrapper& _nCursesPrintOperationWrapper;
};

/*
namespace SignalHandling
{
void posixSignalHandlerInMainConsole(int signal);
void posixSignalHandlerInChatConsole(int signal);
void createPosixSignalsHandling(void(*handlingFunction)(int));

namespace NCurses
{
void resizeHandlerInMainWindow(int);
void resizeHandlerInRegistrationWindow(int);
void resizeHandlerInSignInWindow(int);
void resizeHandlerInChatWindow(int);
} //NCurses
} //SignalHandling
*/
