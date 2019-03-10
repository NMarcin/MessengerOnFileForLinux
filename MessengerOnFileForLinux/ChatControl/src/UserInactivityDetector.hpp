#pragma once

#include <string>

#include "Logger.hpp"
#include "LogSpace.hpp"

class UserInactivityDetector
{
public:
    UserInactivityDetector(const std::string& username);
    UserInactivityDetector() = default;
    ~UserInactivityDetector() = default;

    void setUsername( std::string d){username_=d;}
    void detectUserInactivity();
    bool isUserInactiveDetected() const ;

private: 
    bool isUserInactive() const;

     std::string username_;
    bool isUserInactiveDetected_;

    Logger log_{LogSpace::ChatControl};
};

