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

    static int _isMessengerRunnigTest;
    static void lookForInvitationGT();
    std::thread _waitForInvitation;
    std::string _user = getenv("USER");
    std::string _chatFolderNameWithoutNumber = _user + "_" + _user;
    std::string _pathToChatfile = ENVIRONMENT_PATH::TO_FOLDER::CHATS + "0" + _chatFolderNameWithoutNumber + "/" + _chatFolderNameWithoutNumber;
};
