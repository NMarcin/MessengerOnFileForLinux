#pragma once

#include <gtest/gtest.h>
#include <memory>

#include "Message.hpp"

class MessageFixture : public ::testing::Test
{
public:
    MessageFixture() = default;
    void SetUp();
    void TearDown() {}
    ~MessageFixture() = default;

    void comparingExpectedMessageWithCreatedFromFullString(std::string expectedMessage);
    void comparingExpectedTimeWithTimeFromMessage(std::string expectedMessage);
    void comparingExpectedUsernameWithUsernameFromMessage(std::string expectedMessage);
    void comparingExpectedContentWithContentFromMessage(std::string expectedMessage, std::string messageKind);

    std::unique_ptr<std::string> _expectedReadMessage;
    std::unique_ptr<std::string> _expectedInviterMessage;
    std::unique_ptr<std::string> _expectedRecipientMessage;
};
