#pragma once

#include <gtest/gtest.h>

#include <ChatRequest.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <thread>

class ChatRequestFixture : public ::testing::Test
{
public:
    ChatRequestFixture();
    void SetUp();
    void TearDown();
    ~ChatRequestFixture();

    static int isMessengerRunnigTest;
    static void lookForInvitationGT();
    ChatRequest chatRequest;
    std::thread waitForInvitation;
    std::string user = getenv("USER");
    std::string chatFolderNameWithoutNumber = user + "_" + user;
    std::string pathToChatfile = ENVIRONMENT_PATH::TO_FOLDER::CHATS + "0" + chatFolderNameWithoutNumber + "/" + chatFolderNameWithoutNumber;
};
