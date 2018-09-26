#include <iostream>

#include <LocalUser.hpp>
#include <FileHandling.hpp>

LocalUser::LocalUser()
        : User(getenv("USER"))
{
    log_.function("LoclaUser C-TOR");
}

LocalUser::~LocalUser()
{
    log_.function("LoclaUser D-TOR");
}

LocalUser & LocalUser::getLocalUser()
{
    static LocalUser localUser;
    return localUser;
}
