#include "DirHandler.hpp"

#include <cstring>
#include <filesystem>
#include <print>

std::string DirHandler::cur() {
    try {
        return std::filesystem::current_path().string();
    } catch(...) {
        return "";
    }
}

bool DirHandler::copy(const char* src, const char* dst) {
    try {
        std::filesystem::copy_options options = std::filesystem::copy_options::recursive;
        std::filesystem::copy(src, dst, options);
        return true;
    } catch (std::filesystem::filesystem_error& e) {
        return false;
    }
}

bool DirHandler::exists(const char* dir) {
    try {
        return std::filesystem::is_directory(dir);
    } catch (...) {
        return false;
    }
}

bool DirHandler::mkdir(const char* dir) {
    try {
        return std::filesystem::create_directories(dir);
    } catch (...) {
        return false;
    }
}

bool DirHandler::rmdir(const char* dir) {
    try {
        return std::filesystem::remove_all(dir);
    } catch (...) {
        return false;
    }
}

std::vector<DirectoryEntry> DirHandler::readAll(const char* dir) {
    // Reserce space like small string optimization
    std::vector<DirectoryEntry> names;
    names.reserve(15);

    // Loop module directory
    try {
        for (const auto& item : std::filesystem::directory_iterator(std::string(dir) + "/")) {
            std::string name = item.path().string();
            DirectoryEntry ent;
            ent.name = name.substr(name.find_last_of('/') + 1);
            ent.isDir = item.is_directory();
            names.push_back(ent);
        }
    } catch (std::filesystem::filesystem_error& e) {
        std::println("ERROR: Filesystem could not be read for path \"{}\"", dir);
    } catch (...) {
        std::println("ERROR: Entry failed to be parsed", dir);
    }

    return names;

}

