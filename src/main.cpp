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
#include "Modules.hpp"

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
    std::println("  -h      Prints this menu:");
    std::println();
    std::println("command:");
    std::println("  add     Adds the module to the project");
    std::println("  remove|rem");
    std::println("          Removes the module from the project");
    std::println("  fix     Attempts to fix a broken module");
    std::println();
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
            if (i == args.size() - 1) {
                std::println("\nERROR: No module selected.\n");
                exit((int)CODES::EXIT::NO_MODULE);
            }

            res.module = args[i + 1];
            break;
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
    switch (res.command) {
    case COMMAND::ADD:
        std::println("Adding module \"{}\"", res.module);
        if (Modules::add(res.module)) {
            std::println("Successfully added module \"{}\"", res.module);
        } else {
            std::println("Failed to add module \"{}\"", res.module);
        }
        break;
        
        case COMMAND::REM:
        std::println("Removing module \"{}\"", res.module);
        if (Modules::remove(res.module)) {
            std::println("Successfully removed module \"{}\"", res.module);
        } else {
            std::println("Failed to remove module \"{}\"", res.module);
        }
        break;
        
    case COMMAND::FIX:
        std::println("TODO!");
        break;
        
    default:
        std::println("ERROR: No module selected.");
        break;
    }

    std::println();
	return 0;
}
