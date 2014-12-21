#include <map>
#include <functional>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>

#include "tools/locale.hpp"
#include "tests/tests.hpp"

using TestMap = std::map<std::string, std::function<void ()>>;
using namespace std::string_literals;

static const TestMap TEST_MAP = {
    { "compose"s, test_compose },
    { "list_basic"s, test_list_basic },
    { "list_transform"s, test_list_transform },
    { "list_fold_reduce"s, test_list_fold_reduce },
    { "list_fold_special"s, test_list_fold_special },
    { "list_sublist_extract"s, test_list_sublist_extract },
    { "list_sublist_predicate"s, test_list_sublist_predicate },
    { "list_zip"s, test_list_zip },
    { "maybe"s, test_maybe },
    { "variant"s, test_variant },
};

static void show_usage(const std::string & prog_name)
{
    using std::cerr;
    using std::endl;
    using std::next;

    cerr << "Usage: " << prog_name << " [";
    if (!TEST_MAP.empty())
    {
        cerr << TEST_MAP.begin()->first;
        for (auto it = next(TEST_MAP.begin()); it != TEST_MAP.end(); ++it)
            cerr << " " << it->first;
    }
    cerr << "]" << endl;
}

int main(int argc, char *argv[])
{
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::vector;
    using std::string;
    using tools::group_numbers_locale;

    cout.imbue(group_numbers_locale);

    vector<string> args { argv + 1, argv + argc };

    for (const string & arg: args)
    {
        auto test_found = TEST_MAP.find(arg);
        if (test_found != TEST_MAP.end())
            test_found->second();
        else
            cerr << "Unknown test: " << arg << endl;
    }

    if (args.empty())
        show_usage(*argv);

    return (0);
}
