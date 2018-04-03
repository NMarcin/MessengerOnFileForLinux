#include <iostream>

#include <LocalUser.hpp>
#include <FileHandling.hpp>

LocalUser::LocalUser()
        : User(getenv("USER"))
{
    log.info("LoclaUser C-TOR");
}

LocalUser::~LocalUser()
{
    log.info("LoclaUser D-TOR");
}

LocalUser & LocalUser::getLocalUser()
{
    //log.info("LocalUser::getLocalUser started");
    static LocalUser localUser;
    return localUser;
}
