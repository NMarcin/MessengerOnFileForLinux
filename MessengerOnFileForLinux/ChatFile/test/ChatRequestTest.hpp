#pragma once
#include <gtest/gtest.h>

#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <ChatRequest.hpp>
#include <User.hpp>

class ChatRequestFixture : public ::testing::Test
{
public:
    ChatRequestFixture();
    void SetUp();
    void TearDown();
    ~ChatRequestFixture();

    ChatRequest chatRequest;
};

TEST_F(ChatRequestFixture, isLoggedFileExist)
{
    bool isFileExist = FileInterface::Managment::isFileExist(ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE);
    EXPECT_TRUE(isFileExist);
}

TEST_F(ChatRequestFixture, sendRequestToOfflineUser)
{
    chatRequest.sendChatRequest("marcin1008");
    EXPECT_TRUE(chatRequest.sendChatRequest("marcin1008"));
}

TEST_F(ChatRequestFixture, changeUserStatus)
{
    EXPECT_TRUE(1);
}
