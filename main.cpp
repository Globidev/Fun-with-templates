#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <iostream>

#include "tools/locale.hpp"
#include "tests/tests.hpp"

using TestMap = std::unordered_map<std::string, std::function<void ()>>;
using namespace std::string_literals;

static const TestMap TEST_MAP = {
    { "compose_v1"s, test_compose_v1 },
    { "compose_v2"s, test_compose_v2 },
    { "list_basic"s, test_list_basic },
};

int main(int argc, char *argv[])
{
    std::cout.imbue(locale);

    std::vector<std::string> args { argv + 1, argv + argc };
    for (const std::string & arg: args)
    {
        auto test_found = TEST_MAP.find(arg);
        if (test_found != TEST_MAP.end())
            test_found->second();
    }

    return (0);
}
