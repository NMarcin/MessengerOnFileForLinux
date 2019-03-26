#pragma once

#include <Logger.hpp>
#include <LogSpace.hpp>

class LocalUser
{
public:
    static LocalUser& getLocalUser();
    const std::string getUsername() const;

private:
    LocalUser();
    ~LocalUser() = default;
    LocalUser(const LocalUser &) = delete;
    LocalUser& operator=(const LocalUser &) = delete;

    const std::string username_;

    Logger log_ {LogSpace::UserService};
};
