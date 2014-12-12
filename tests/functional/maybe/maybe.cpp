#include "functional/maybe.hpp"

#include <cassert>
#include <iostream>

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
    assert(from_maybe(42, just(3)) == 3);
    assert(from_maybe(42, nothing<int>) == 42);
    using ML = std::vector<maybe_t<int>>;
    using L = std::vector<int>;
    assert((cat_maybes(ML { just(1), nothing<int>, just(3) }) == L { 1, 3 }));
    assert((cat_maybes(ML { nothing<int>, nothing<int> }) == L { }));
    auto even = [](auto a) { return a % 2 ? nothing<int> : just(a); };
    assert((map_maybe(even, L { 1, 2, 3, 4, 5, 6 }) == L { 2, 4, 6 }));
    assert((map_maybe(even, L { }) == L { }));
}
