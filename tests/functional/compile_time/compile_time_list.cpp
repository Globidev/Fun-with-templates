#include <utility>

#include "functional/compile_time/list.hpp"

struct array_builder {

    template <class T, class... Ts>
    constexpr auto operator()(T && t, Ts &&... ts) const {
        using functional::compile_time::array;
        using std::forward;

        return array<T, sizeof...(Ts) + 1> { forward<T>(t), forward<Ts>(ts)... };
    }

};

void test_list_basic_compile_time(void)
{
    using namespace functional::compile_time::list;
    using functional::compile_time::array;

    array_builder l;

    static_assert(l(1, 2, 3) == l(1, 2, 3), "fail");
    static_assert(append(l(1, 2, 3), l(4, 5, 6)) == l(1, 2, 3, 4, 5, 6), "fail");
    static_assert(head(l(42, 1337, 10)) == 42, "fail");
    static_assert(last(l(42, 1337, 10)) == 10, "fail");
    static_assert(tail(l(42, 1337, 10)) == l(1337, 10), "fail");
    static_assert(init(l(42, 1337, 10)) == l(42, 1337), "fail");
    static_assert(null(l(42, 1337, 10)) == false, "fail");
    static_assert(null(array<int, 0>()) == true, "fail");
    static_assert(length(l(42, 1337, 10)) == 3, "fail");
    static_assert(length(array<double, 0>()) == 0, "fail");
}

void test_list_transform_compile_time(void)
{
    using namespace functional::compile_time::list;
    array_builder l;

    // No constexpr lambda. Declaring a functor the old fashion way
    struct {
        constexpr auto operator()(int a) const { return a * 4.2; }
    } times_four_point_two;

    static_assert(map(times_four_point_two, l(1, 2, 3)) == l(4.2, 8.4, 3 * 4.2), "fail"); // writing 12.6 fails here. Most likely due to IEEE
    static_assert(reverse(l(1, 2, 3, 42, 1337)) == l(1337, 42, 3, 2, 1), "fail");
    static_assert(intersperse(42, l(1)) == l(1), "fail");
    static_assert(intersperse(42, l(1, 2, 3)) == l(1, 42, 2, 42, 3), "fail");
}
