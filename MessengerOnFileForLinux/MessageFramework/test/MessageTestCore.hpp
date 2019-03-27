#pragma once

#include <gtest/gtest.h>
#include <Message.hpp>
#include <memory>

class MessageFixture : public ::testing::Test
{
public:
    MessageFixture() = default;
    void SetUp();
    void TearDown() {};
    ~MessageFixture() = default;

    void comparingExpectedMessageWithCreatedFromFullString(std::string expectedMessage);
    void comparingExpectedTimeWithTimeFromMessage(std::string expectedMessage);
    void comparingExpectedUsernameWithUsernameFromMessage(std::string expectedMessage);
    void comparingExpectedContentWithContentFromMessage(std::string expectedMessage, std::string messageKind);

    std::unique_ptr<std::string> expectedReadMessage;
    std::unique_ptr<std::string> expectedInviterMessage;
    std::unique_ptr<std::string> expectedRecipientMessage;
};
