#pragma once

constexpr const char* MODULES_ENV   = "CMOD_MODULES_DIR";
constexpr const char* MODULES_DIR   = "./modules/";
constexpr const char* VERSION       = "1.0";

enum class COMMAND {
    INVALID,
    LIST,
    ADD,
    REM,
    FIX,
};

namespace CODES {
    enum class EXIT {
        GOOD,
        NO_MODULE,
    };
}

