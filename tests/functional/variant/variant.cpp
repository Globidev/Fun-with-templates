#include "functional/variant.hpp"

#include <cassert>
#include <string>
#include <vector>

using namespace std::string_literals;
using namespace functional::variant;

struct test { int a; double b; std::string c; };

using simple_variant = variant_t<int, double, char>;
using complex_variant = variant_t<int, std::string, std::vector<double>, test>;

template <size_t i>
struct visitor {

    int operator()(int a) const { return a + i; }
    int operator()(const test & t) const { return t.a + i; }
    template <class T> // T matches all unspecialized types (string and vector)
    int operator()(const T & t) const { return t.size() + i; }

};

void test_variant(void)
{
    simple_variant var { 4.5 };
    var.visit([](auto v) { assert(v == 4.5); });
    var = 'a';
    var.visit([](auto v) { assert(v == 'a'); });
    auto var2 = var;
    var2.visit([](auto v) { assert(v == 'a'); });

    complex_variant var3 { "lol"s };
    assert(var3.visit(visitor<10> {}) == 13);
    using third_type = typename complex_variant::pack::type_at<2>::type;
    var3 = third_type { 1.2, 3, 4.2, 13.37 };
    assert(var3.visit(visitor<38> {}) == 42);
    assert(var3.visit(
        [](auto a) -> size_t { return a + 38; },
        [](auto a) -> size_t { return a.size() + 38; },
        [](auto a) -> size_t { return a.size() + 38; },
        [](auto a) -> size_t { return a.a + 38; }
    ) == 42);
}
