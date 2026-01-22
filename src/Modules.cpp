#include "Modules.hpp"

#include <print>

#include "Constants.hpp"
#include "DirHandler.hpp"

// Try to find path traversal or other shenanigans
bool verifyModule(const std::string& module) {
    if (module.length() == 0) {
        return false;
    }

    if (module.find("/") != std::string::npos) {
        return false;
    }

    if (module.find("\\") != std::string::npos) {
        return false;
    }

    return true;
}

// Finds a module in the main "repo"
bool findModule(const std::string& module) {
    const char* env = std::getenv(MODULES_ENV);
    if (env == nullptr) {
        std::println("ERROR: Could not read env.");
        return false;
    }
    
    std::string path = std::string(env) + std::string("/") + module;
    return DirHandler::exists(path.c_str());
}

// Checks modules folder
bool checkModule(const std::string& module) {
    std::string path = MODULES_DIR + module;
    return DirHandler::exists(path.c_str());
}

// Copies a module from "repo"
bool copyModule(const std::string& module) {
    const char* env = std::getenv(MODULES_ENV);
    if (env == nullptr) {
        std::println("ERROR: Could not read env.");
        return false;
    }

    std::string src = std::string(env) + std::string("/") + module;
    std::string dst = DirHandler::cur() + std::string("/") + std::string(MODULES_DIR) + module;

    if (!DirHandler::mkdir(dst.c_str())) {
        return false;
    }
    return DirHandler::copy(src.c_str(), dst.c_str());
}

// Removes module from local folder
bool removeModule(const std::string& module) {
    std::string path = MODULES_DIR + module;
    return DirHandler::rmdir(path.c_str());
}

bool Modules::add(const std::string& module) {
    // Valid name format
    if (!verifyModule(module)) {
        std::println("ERROR: Invalid module format.");
        return false;
    }
    
    // Module exists in "repo"
    if (!findModule(module)) {
        std::println("ERROR: Module does not exist.");
        return false;
    }
    
    // Copy module
    if (!copyModule(module)) {
        std::println("ERROR: Could not add module.");
        return false;
    }
    
    return true;
}

bool Modules::remove(const std::string& module) {
    // Valid name format
    if (!verifyModule(module)) {
        std::println("ERROR: Invalid module format.");
        return false;
    }
    
    // Check module exists in current project
    if (!checkModule(module)) {
        std::println("ERROR: Module does not exist.");
        return false;
    }
    
    // Remove module
    if (!removeModule(module)) {
        std::println("ERROR: Could not remove module.");
        return false;
    }
    
    return true;
}

