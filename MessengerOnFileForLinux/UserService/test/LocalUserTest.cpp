#include <gtest/gtest.h>

#include "LocalUser.hpp"

TEST(LocalUserTest, isLocalUsernameIsCorrect)
{
    const std::string localUsername = getenv("USER");
    EXPECT_EQ(localUsername, LocalUser::getLocalUser().getUsername());
}

