#pragma once
#include <string>

#include "GlobalVariables.hpp"

namespace guard
{
    bool isGuardExist(const std::string & fileName, FileFlagType type);
    bool setFileFlag(const std::string & fileName, FileFlagType type);
    bool removeFileFlag(const std::string & fileName, FileFlagType type);
}
