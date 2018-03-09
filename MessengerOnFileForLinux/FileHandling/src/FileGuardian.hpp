#pragma once
#include <string>

#include "GlobalVariables.hpp"

namespace guard
{
    bool isGuardExist(const std::string & fileName, FileFlagType type, const std::string & pathToFile = "");
    bool setFileFlag(const std::string & fileName, FileFlagType type, const std::string & pathToFile = "");
    bool removeFileFlag(const std::string & fileName, FileFlagType type, const std::string & pathToFile = "");
}
