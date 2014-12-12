#include "functional/maybe.hpp"

#include <cassert>

using namespace std::string_literals;

void test_maybe(void)
{
    using namespace functional::maybe;

    auto to_string = [](auto v) { return std::to_string(v); };
    assert(maybe("lol"s, to_string, just(3)) == "3"s);
    assert(maybe("lol"s, to_string, nothing<int>) == "lol"s);
    assert(is_just(just("abc"s)) == true);
    assert(is_just(nothing<char>) == false);
    assert(is_nothing(just("abc"s)) == false);
    assert(is_nothing(nothing<char>) == true);
}
