#include "disc_math.hpp"
#include <iostream>
#include <string>
#include <map>
#include <windows.h>

void print_help()
{
    std::cout << "Usage: program_name [OPTION]\n"
              << "Available modes:\n"
              << "  -h, --help      Show this help message\n"
              << "  -n1, --exercise1     Turn on task number 1 solving mode\n"
              << "  -n1, --exercise2     Turn on task number 2 solving mode\n";
}

int main(int argc, char *argv[])
{
    using namespace disc_math;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::map<std::string, bool> modes = {
        {"exercise1", false},
        {"exercise2", false},
    };

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        constexpr auto hash = [](const char *str)
        {
            unsigned int hash = 5381;
            while (int c = *str++)
                hash = ((hash << 5) + hash) + c;
            return hash;
        };

        switch (hash(arg.c_str()))
        {
        case hash("-h"):
        case hash("--help"):
            print_help();
            return 0;
        case hash("-m"):
        case hash("--exercise1"):
            modes["exercise1"] = true;
            break;
        case hash("-g"):
        case hash("--exercise2"):
            modes["exercise2"] = true;
            break;
        default:
            std::cerr << "Unknown option: " << arg << "\n";
            print_help();
            return 1;
        }
    }
    if (modes["exercise1"] && modes["exercise2"])
    {
        std::cerr << "Error: Cannot use both exercise1 and exercise1 simultaneously\n";
        return 1;
    }

    if (modes["verbose"])
    {
        std::cout << "Selected modes:\n";
        for (const auto &[mode, enabled] : modes)
        {
            if (enabled)
            {
                std::cout << "  " << mode << "\n";
            }
        }
    }
    if (modes["exercise1"])
    {
        auto const res = first_exercise();
    }
    else if (modes["exercise2"])
    {
        auto const res1 = second_exercise();
    }
    else
    {
        if (modes["verbose"])
            std::cout << "Running in default mode\n";
    }

    return 0;
}