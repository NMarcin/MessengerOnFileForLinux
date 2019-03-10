#pragma once

#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"

class UserInactivityDetectorFixture : public ::testing::Test
{
public:
    UserInactivityDetectorFixture() : userInactivityDetector_(getenv("USER")){}
    void SetUp(){}
    void TearDown(){}
    ~UserInactivityDetectorFixture(){}

    UserInactivityDetector userInactivityDetector_;
};
