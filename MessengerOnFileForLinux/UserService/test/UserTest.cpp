#include <gtest/gtest.h>

#include <User.hpp>
#include <LocalUser.hpp>

TEST(UserTest, setUpUsernameByCtor)
{
    User user("mwoznia2");
    EXPECT_EQ("mwoznia2", user.getUsername());
}

TEST(UserTest, isPossibleSetUsername)
{
    User user;
    EXPECT_EQ("", user.getUsername());
    user.setUsername("mnurzyns");
    EXPECT_NE("", user.getUsername());
    EXPECT_EQ("mnurzyns", user.getUsername());
}

TEST(UserTest, isSetPasswordWorksCorretly)
{
    User user;
    EXPECT_EQ("", user.getPassword());
    user.setPassword("123456789");
    EXPECT_NE("", user.getPassword());
    EXPECT_EQ("123456789", user.getPassword());
}
/*
TEST(LocalUserTest, isLocalUsernameIsCorrect)
{
    std::string localUsername = getenv("USER");
    EXPECT_EQ(localUsername, LocalUser::getLocalUser().getUsername());
}
*/
