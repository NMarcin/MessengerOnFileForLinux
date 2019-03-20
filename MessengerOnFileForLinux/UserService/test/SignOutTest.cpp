#include <gtest/gtest.h>

#include <SignOut.hpp>
#include "SignOutTestCore.hpp"

TEST_F(SignOutTestFixture, isUserSignOutReturnTrueWhenUserIsLogged)
{
    signInUser();
    EXPECT_TRUE(signOut.signOutUser());
}

TEST_F(SignOutTestFixture, isUserSignOutReturnFalseWhenUserIsNotLogged)
{
    EXPECT_FALSE(signOut.signOutUser());
}
