#include <gtest/gtest.h>

#include <LocalUser.hpp>

TEST(LocalUserTest, isSetPasswordWorksCorretly)
{
    EXPECT_EQ("", LocalUser::getLocalUser().getPassword());
    LocalUser::getLocalUser().setPassword("123456789");
    EXPECT_NE("", LocalUser::getLocalUser().getPassword());
    EXPECT_EQ("123456789", LocalUser::getLocalUser().getPassword());
}

TEST(LocalUserTest, isLocalUsernameIsCorrect)
{
    std::string localUsername = getenv("USER");
    EXPECT_EQ(localUsername, LocalUser::getLocalUser().getUsername());
}

