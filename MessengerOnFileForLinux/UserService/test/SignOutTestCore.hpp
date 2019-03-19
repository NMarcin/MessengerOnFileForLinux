#pragma once

#include <gtest/gtest.h>

#include "SignOut.hpp"

class SignOutTestFixture : public ::testing::Test
{
public:
    SignOutTestFixture() {}
    void SetUp() {}
    void TearDown() {}
    ~SignOutTestFixture() {}

    SignOut signOut;
};
