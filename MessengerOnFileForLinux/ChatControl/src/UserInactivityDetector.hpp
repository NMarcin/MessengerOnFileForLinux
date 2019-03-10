#pragma once

#include <string>

#include "Logger.hpp"
#include "LogSpace.hpp"

class UserInactivityDetector
{
public:
    UserInactivityDetector(const std::string& username);
    ~UserInactivityDetector() = default;

    void detectUserInactivity();
    bool isUserInactiveDetected() const ;

private: 
    bool isUserInactive() const;

    const std::string username_;
    bool isUserInactiveDetected_;

    Logger log_{LogSpace::ChatControl};
};

