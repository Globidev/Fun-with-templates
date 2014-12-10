#include <utility>

#include "functional/compile_time/list.hpp"

template <class T, class... Ts>
static constexpr auto make_array(T && t, Ts &&... ts)
{
    using functional::compile_time::array;
    using std::forward;

    return array<T, sizeof...(Ts) + 1> { forward<T>(t), forward<Ts>(ts)... };
}

void test_list_basic_compile_time(void)
{
    using namespace functional::compile_time::list;
    using functional::compile_time::array;

    static_assert(make_array(1, 2, 3) == make_array(1, 2, 3), "fail");
    static_assert(append(make_array(1, 2, 3), make_array(4, 5, 6)) ==
                  make_array(1, 2, 3, 4, 5, 6), "fail");
    static_assert(head(make_array(42, 1337, 10)) == 42, "fail");
    static_assert(last(make_array(42, 1337, 10)) == 10, "fail");
    static_assert(tail(make_array(42, 1337, 10)) ==
                  make_array(1337, 10), "fail");
    static_assert(init(make_array(42, 1337, 10)) ==
                  make_array(42, 1337), "fail");
    static_assert(null(make_array(42, 1337, 10)) == false, "fail");
    static_assert(null(array<int, 0>()) == true, "fail");
    static_assert(length(make_array(42, 1337, 10)) == 3, "fail");
    static_assert(length(array<double, 0>()) == 0, "fail");
}

void test_list_transform_compile_time(void)
{
    using namespace functional::compile_time::list;

    // No constexpr lambda. Declaring a functor the old fashion way
    struct {
        constexpr auto operator()(int a) const { return a * 4.2; }
    } times_four_point_two;

    static_assert(map(times_four_point_two, make_array(1, 2, 3)) ==
                  make_array(4.2, 8.4, 3 * 4.2), "fail"); // writing 12.6 fails
                                                          // here. Most likely
                                                          // due to IEEE
    static_assert(reverse(make_array(1, 2, 3, 42, 1337)) ==
                  make_array(1337, 42, 3, 2, 1), "fail");
    static_assert(intersperse(42, make_array(1)) == make_array(1), "fail");
    static_assert(intersperse(42, make_array(1, 2, 3)) ==
                  make_array(1, 42, 2, 42, 3), "fail");
}
