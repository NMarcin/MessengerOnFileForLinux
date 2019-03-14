#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"
#include "UserInactivityDetectorTestCore.hpp"

TEST_F(UserInactivityDetectorFixture, isUserInactiveDetectedIsSetToFalseInCtor)
{
    EXPECT_FALSE(userInactivityDetector_.isUserInactiveDetected());
}

TEST_F(UserInactivityDetectorFixture, isUserInactiveDetectedReturnsFalseWhenUserHasActiveApplicationProcess)
{
    userInactivityDetector_.detectUserInactivity();
    EXPECT_FALSE(userInactivityDetector_.isUserInactiveDetected());
}

TEST(UserInactivityDetectorTest, isUserInactiveDetectedOfNonExistigUserReturnsTrue)
{
    const std::string username  = "nonExisitingUser";
    UserInactivityDetector userInactivityDetector_(username);
    userInactivityDetector_.detectUserInactivity();
    EXPECT_TRUE(userInactivityDetector_.isUserInactiveDetected());
}
