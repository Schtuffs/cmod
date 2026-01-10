#pragma once

#include <string>

namespace Modules {
    // Attempts to add a module to local scope
    bool add(const std::string& module);

    // Attempts to remove a module from local scope
    bool remove(const std::string& module);
}

