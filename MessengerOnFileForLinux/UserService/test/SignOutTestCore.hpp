#pragma once

#include <gtest/gtest.h>

#include "SignOut.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"

class SignOutTestFixture : public ::testing::Test
{
public:
    SignOutTestFixture() {}
    void SetUp() {}
    void TearDown() {}
    ~SignOutTestFixture() {}

    void signInUser()
    {
        const std::string USER = getenv("USER");
        const std::string rowInLoggedFile = "[" + USER + "][0]";
        FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, rowInLoggedFile);
    }

    SignOut signOut;
};
