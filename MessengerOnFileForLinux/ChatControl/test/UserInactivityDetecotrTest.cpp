#include <gtest/gtest.h>

#include "UserInactivityDetector.hpp"
#include "UserInactivityDetectorTestCore.hpp"

TEST_F(UserInactivityDetectorFixture, isUserInactiveDetectedIsSetToFalseInCtor)
{
    EXPECT_FALSE(_userInactivityDetector.isUserInactiveDetected());
}

TEST_F(UserInactivityDetectorFixture, isUserInactiveDetectedReturnsFalseWhenUserHasActiveApplicationProcess)
{
    _userInactivityDetector.detectUserInactivity();
    EXPECT_FALSE(_userInactivityDetector.isUserInactiveDetected());
}

TEST(UserInactivityDetectorTest, isUserInactiveDetectedOfNonExistigUserReturnsTrue)
{
    const std::string username  = "nonExisitingUser";
    UserInactivityDetector userInactivityDetector_(username);
    userInactivityDetector_.detectUserInactivity();
    EXPECT_TRUE(userInactivityDetector_.isUserInactiveDetected());
}
