#pragma once

#include <string>
#include <vector>

typedef struct DirectoryEntry {
    std::string name;
    bool isDir;
} DirectoryEntry;

namespace DirHandler {
    // Returns the current directory
    std::string cur();
    
    // Recursively copies a file
    bool copy(const char* src, const char* dst);

    // Check if a directory exists
    bool exists(const char* dir);

    // Creates a directory
    bool mkdir(const char* dir);

    // Removes a directory recursively
    bool rmdir(const char* dir);

    // Gets all filenames in given directory
    std::vector<DirectoryEntry> readAll(const char* dir);
}

