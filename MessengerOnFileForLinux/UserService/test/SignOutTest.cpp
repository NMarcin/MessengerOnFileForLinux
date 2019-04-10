#include <gtest/gtest.h>

#include <SignOut.hpp>
#include "SignOutTestCore.hpp"

TEST_F(SignOutTestFixture, isUserSignOutReturnTrueWhenUserIsLogged)
{
    signInUser();
    EXPECT_TRUE(_signOut.signOutUser());
}

TEST_F(SignOutTestFixture, isUserSignOutReturnFalseWhenUserIsNotLogged)
{
    EXPECT_FALSE(_signOut.signOutUser());
}
