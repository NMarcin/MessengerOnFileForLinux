#pragma once
#include <string>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include <ChatRequest.hpp>
#include <iostream>

static constexpr char registeredFile[] = "registered.txt";
static constexpr char loggedFile[] = "logged.txt";
static constexpr char registeredFilePath[] = "/home/messenger/configuration/";
static constexpr char loggedFilePath[] = "/home/messenger/configuration/";
static constexpr char chatFilePath[] = "/home/messenger/chat/";


static const std::string userActiveStatus = "0";
static const std::string userBussyStatus = "1";

static constexpr int usernameFieldInLoggedFile = 0;
static constexpr int statusFieldInLoggedFile = 1;
static constexpr int pidFieldInLoggedFile = 2;

static constexpr int usernameFieldInRegisteredFile = 0;
static constexpr int passwordFieldInRegisteredFile = 1;
static constexpr int dateTimeFieldInRegisteredFile = 2;


static constexpr int timeToWaitForAnswer = 20;


/** To do jakiegos inita ***********************************/
static void sigusr1Handler(int sig_num, siginfo_t *info, void *context)
{
    if (NULL == info)
    {
        std::cerr << "WARNING: info = NULL" << std::endl;
    }
    ChatRequest chatRequest;
    chatRequest.answerForChatRequest(info -> si_pid);
}

static void initSigusr1Action()
{
    sigset_t iset;
    struct sigaction act;
    sigemptyset(&iset);

    act.sa_sigaction = sigusr1Handler;
    act.sa_mask = iset;
    act.sa_flags |= SA_SIGINFO;

    sigaction(SIGUSR1, &act, NULL);
}

/** **********************************************************/


enum class FileFlagType
{
    guardian,
    newFlag
};
