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
              << "  -n2, --exercise2     Turn on task number 2 solving mode\n"
              << "  -c1, --combinators1     Turn on task combinators 1 solving mode\n"
              << "  -c2, --combinators2     Turn on task combinators 2 solving mode\n"
              << "  -c3, --combinators3     Turn on task combinators 3 solving mode\n";
}

int main(int argc, char *argv[])
{
    using namespace disc_math;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::map<std::string, bool> modes = {
        {"exercise1", false},
        {"exercise2", false},
        {"combinators1", false},
        {"combinators2", false},
        {"combinators3", false},
    };

    int count_of_flags = 0;
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
        case hash("-n1"):
        case hash("--exercise1"):
            modes["exercise1"] = true;
            count_of_flags++;
            break;
        case hash("-n2"):
        case hash("--exercise2"):
            modes["exercise2"] = true;
            count_of_flags++;
            break;
        case hash("-c1"):
        case hash("--combinators1"):
            modes["combinators1"] = true;
            count_of_flags++;
            break;
        case hash("-c2"):
        case hash("--combinators2"):
            modes["combinators2"] = true;
            count_of_flags++;
            break;
        case hash("-c3"):
        case hash("--combinators3"):
            modes["combinators3"] = true;
            count_of_flags++;
            break;
        default:
            std::cerr << "Unknown option: " << arg << "\n";
            print_help();
            return 1;
        }
    }
    if (1 < count_of_flags)
    {
        std::cerr << "Error: Cannot use more than 1 flag at once\n";
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
        first_exercise();
    }
    else if (modes["exercise2"])
    {
        second_exercise();
    }
    else if (modes["combinators1"])
    {
        first_combinator_exercise();
    }
    else if (modes["combinators2"])
    {
        second_combinator_exercise();
    }
    else if (modes["combinators3"])
    {
        third_combinator_exercise();
    }
    else
    {
        if (modes["verbose"])
            std::cout << "Running in default mode\n";
    }

    return 0;
}