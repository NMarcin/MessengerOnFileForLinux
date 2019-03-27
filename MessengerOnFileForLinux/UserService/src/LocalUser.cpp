#include <iostream>

#include <LocalUser.hpp>
#include <FileHandling.hpp>

LocalUser::LocalUser()
    : username_(getenv("USER"))
{
    log_.function("LoclaUser C-TOR");
}

LocalUser& LocalUser::getLocalUser()
{
    static LocalUser localUser;
    return localUser;
}

const std::string LocalUser::getUsername() const
{
    log_.function("LocalUser::getUsername() started");
    return username_;
}
