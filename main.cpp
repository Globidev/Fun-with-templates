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
    { "list_transform"s, test_list_transform },
    { "list_fold_basic"s, test_list_fold_basic },
    { "list_fold_special"s, test_list_fold_special },
};

int main(int argc, char *argv[])
{
    using std::cout;
    using tools::group_numbers_locale;
    using std::vector;
    using std::string;

    cout.imbue(group_numbers_locale);

    vector<string> args { argv + 1, argv + argc };
    for (const string & arg: args)
    {
        auto test_found = TEST_MAP.find(arg);
        if (test_found != TEST_MAP.end())
            test_found->second();
    }

    return (0);
}
