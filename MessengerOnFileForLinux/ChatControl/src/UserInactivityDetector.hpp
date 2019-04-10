#pragma once

#include <string>

#include "Logger.hpp"
#include "LogSpace.hpp"

class UserInactivityDetector
{
public:
    UserInactivityDetector(const std::string& username);
    ~UserInactivityDetector() = default;

    UserInactivityDetector(UserInactivityDetector &&) = delete;
    UserInactivityDetector operator=(UserInactivityDetector &&) = delete;
    UserInactivityDetector(const UserInactivityDetector &) = delete;
    UserInactivityDetector operator=(const UserInactivityDetector &) = delete;

    void detectUserInactivity();
    bool isUserInactiveDetected() const ;

private: 
    bool isUserInactive() const;

    const std::string _username;
    bool _isUserInactiveDetected;

    Logger _log{LogSpace::ChatControl};
};

