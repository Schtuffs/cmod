#pragma once

#include <string>

namespace DirHandler {
    // Returns the current directory
    std::string cur();
    
    // Recursively copies a file
    bool copy(const char* src, const char* dst);

    // Check if a directory exists
    bool exists(const char* dirName);

    // Creates a directory
    bool mkdir(const char* dirName);

    // Removes a directory recursively
    bool rmdir(const char* dirName);
}

