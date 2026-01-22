/**
 * Plans:
 * 1. command: cmod
 * 2. shall function similar to proj command
 * 3. modules shall be added to my programs with "add" arg
 * 4. modules should be removable with "remove" or "rem" arg
 * 5. should handle creating modules folders and filesystems
 */

#include <iostream>
#include <print>
#include <string>
#include <vector>

#include "Constants.hpp"
#include "DirHandler.hpp"
#include "Modules.hpp"

bool IN_VERBOSE_MODE = false;

std::vector<std::string> parseArgs(int argc, char** argv) {
    std::vector<std::string> args;
    args.reserve(argc - 1);

    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }

    return args;
}

void printHelp() {
    std::println();
    std::println("Usage: cmod [options] [command] [module]");
    std::println("options:");
    std::println("  -h          Prints this menu");
    std::println("  --verbose   Prints helpful debug information");
    std::println();
    std::println("command:");
    std::println("  list        Lists available modules");
    std::println("  add         Adds the module to the project");
    std::println("  remove|rem  Removes the module from the project");
    std::println("  fix         Attempts to fix a broken module");
    std::println();
}

void printModules() {
    auto dirItems = DirHandler::readAll(MODULES_DIR);
    if (dirItems.size() == 0) {
        std::println("\nNo modules added.");
        return;
    }

    std::println("\nModules:");
    for (const auto& item : dirItems) {
        std::println("{}", item.name);
    }
}

void printVersion() {
    std::println();
    std::println("  CMOD personal C/C++ Module Manager");
    std::println("Version {}", VERSION);
    std::println();
}

typedef struct ArgsResult {
    COMMAND command;
    std::string module;
} ArgsResult;

ArgsResult handleArgs(const std::vector<std::string>& args) {
    ArgsResult res{};
    
    if (args.size() == 0) {
        printHelp();
        exit((int)CODES::EXIT::GOOD);
    }

    for (size_t i = 0; i < args.size(); i++) {
        const std::string& arg = args[i];
        
        // Help menu
        if (arg.compare("-h") == 0) {
            printHelp();
            exit((int)CODES::EXIT::GOOD);
        }
        
        // Version menu
        if (arg.compare("-v") == 0) {
            printVersion();
            exit((int)CODES::EXIT::GOOD);
        }
        
        // Version menu
        if (arg.compare("--verbose") == 0) {
            IN_VERBOSE_MODE = true;
            continue;
        }
        
        // list modules
        if (arg.compare("list") == 0) {
            printModules();
            std::println();
            exit((int)CODES::EXIT::GOOD);
        }
        
        // add module
        if (arg.compare("add") == 0) {
            res.command = COMMAND::ADD;
        }
        
        // remove module
        if (arg.compare("rem") == 0 || arg.compare("remove") == 0) {
            res.command = COMMAND::REM;
        }
        
        // remove module
        if (arg.compare("fix") == 0) {
            res.command = COMMAND::FIX;
        }
        
        // Choose the next arg as the module
        if (res.command != COMMAND::INVALID) {
            if (i < args.size() - 1) {
                res.module = args[i + 1];
                break;
            }
            else {
                std::println("\nERROR: No module selected.\n");
                exit((int)CODES::EXIT::NO_MODULE);
            }
        }
    }

    return res;
}

int main(int argc, char** argv) {
    // Get proper input
    auto args = parseArgs(argc, argv);
    auto res = handleArgs(args);

    // Manage commands
    std::println();
    if (IN_VERBOSE_MODE) {
        std::println("Command: {}", static_cast<int>(res.command));
    }

    switch (res.command) {
        case COMMAND::ADD: {
            std::println("Adding module \"{}\"", res.module);
            if (Modules::add(res.module)) {
                std::println("Successfully added module \"{}\"", res.module);
            } else {
                std::println("Failed to add module \"{}\"", res.module);
            }
            break;
        }
        case COMMAND::REM: {
            std::println("Removing module \"{}\"", res.module);
            if (Modules::remove(res.module)) {
                std::println("Successfully removed module \"{}\"", res.module);
            } else {
                std::println("Failed to remove module \"{}\"", res.module);
            }
            break;
        }
        case COMMAND::FIX: {
            std::println("TODO!");
            break;
        }
        default: {
            std::println("ERROR: No module selected.");
            break;
        }
    }

    std::println();
	return 0;
}
