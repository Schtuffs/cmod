#include "DirHandler.hpp"

#include <filesystem>

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

bool DirHandler::exists(const char* dirName) {
    try {
        return std::filesystem::is_directory(dirName);
    } catch (...) {
        return false;
    }
}

bool DirHandler::mkdir(const char* dirName) {
    try {
        return std::filesystem::create_directories(dirName);
    } catch (...) {
        return false;
    }
}

bool DirHandler::rmdir(const char* dirName) {
    try {
        return std::filesystem::remove_all(dirName);
    } catch (...) {
        return false;
    }
}

