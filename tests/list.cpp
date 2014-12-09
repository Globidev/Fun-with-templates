#include <cassert>
#include <iostream>
#include <functional>

#include <vector>
#include <deque>
#include <list>
#include <forward_list>

#include "tools/benchmark.hpp"
#include "tools/type_name.hpp"

#include "functional/list.hpp"

static constexpr size_t ITER_COUNT = 1'000'000;

template <template <template <class...> class> class TestF> struct test {

    template <
        template <class...> class C1,
        template <class...> class C2,
        template <class...> class... Cs
    >
    static void with() {
        with<C1>();
        with<C2, Cs...>();
    }

    template <template <class...> class C>
    static void with() {
        using std::cout;
        using std::endl;
        using tools::pretty_name;

        TestF<C> test_func;

        cout << "Testing: " << pretty_name<TestF<C>>()
             << " (" << ITER_COUNT << " iterations)"
             << endl << endl;
        test_func();
        cout << endl << endl;
    }

};

template <class F, class T>
auto assertN(const char *description, const F & f, const T & t)
{
    tools::benchmark b { description };

    for (size_t i = 0; i < ITER_COUNT; ++i)
        assert( (f() == t) );
}

template <template <class...> class C> struct container_builder {

    template <class V, class... Vs>
    auto operator()(const V & v, const Vs &... vs) const {
        return C<V> { v, vs... };
    };

    auto operator()() const {
        return C<int>{};
    }

};


template <template <class...> class C> struct basic {

    void operator()(void) const {
        using namespace functional::list;
        using std::bind;

        container_builder<C> l;

        assertN("++", bind(append, l(1, 2, 3), l(4, 5, 6)), l(1, 2, 3, 4, 5, 6));
        assertN("head", bind(head, l(1, 2, 3)), 1);
        assertN("last", bind(last, l(1, 2, 3)), 3);
        assertN("tail", bind(tail, l(1, 2, 3)), l(2, 3));
        assertN("init", bind(init, l(1, 2, 3)), l(1, 2));
        assertN("null (false)", bind(null, l(1, 2, 3)), false);
        assertN("null (true)", bind(null, C<int>{}), true);
        assertN("length", bind(length, l(1, 2, 3)), 3);
    }

};

template <template <class...> class C> struct transform {

    void operator()(void) const {
        using namespace functional::list;
        using std::bind;

        container_builder<C> l;

        auto x = 1337.42;
        auto times_x = [x](auto a) { return a * x; };
        assertN("map", bind(map, times_x, l(42, 1337)), l(56171.64, 1788130.54));
        assertN("reverse", bind(reverse, l(1, 2, 3)), l(3, 2, 1));
        assertN("intersperse", bind(intersperse, 4, l(1, 2, 3)), l(1, 4, 2, 4, 3));
        assertN("intercalate", bind(intercalate, l(4), l(l(1), l(2), l(3))),
                l(1, 4, 2, 4, 3));
    }

};

template <template <class...> class C> struct fold_reduce {

    void operator()(void) const {
        using namespace functional::list;
        using std::bind;

        container_builder<C> l;

        auto fold_plus_42 = [](auto r, auto v) { return v + r + 42; };
        assertN("foldl", bind(foldl, fold_plus_42, 42, l(1, 2, 3)), 174);
        assertN("foldl1", bind(foldl1, fold_plus_42, l(42, 1, 2, 3)), 174);
        assertN("foldr", bind(foldr, fold_plus_42, 42, l(1, 2, 3)), 174);
        assertN("foldr1", bind(foldr1, fold_plus_42, l(42, 1, 2, 3)), 174);
    }

};

template <template <class...> class C> struct fold_special {

    void operator()(void) const {
        using namespace functional::list;
        using std::bind;

        container_builder<C> l;

        assertN("concat", bind(concat, l(l(1, 2), l(3, 4))), l(1, 2, 3, 4));
        auto f = [&l](auto x) { return l(x - 1, x, x + 1); };
        assertN("concatMap", bind(concat_map, f, l(1, 2, 3)), l(0, 1, 2, 1, 2, 3, 2, 3, 4));
        assertN("and (true)", bind(and_, l(true, true, true)), true);
        assertN("and (false)", bind(and_, l(true, false, true)), false);
        assertN("and (empty)", bind(and_, l()), true);
        assertN("or (true)", bind(or_, l(false, true, false)), true);
        assertN("or (false)", bind(or_, l(false, false, false)), false);
        assertN("or (empty)", bind(or_, l()), false);
        auto evenMod5 = [](auto x) { return !(x % 5) && !(x % 2); };
        assertN("all (true)", bind(all, evenMod5, l(0, 10, 20)), true);
        assertN("all (false)", bind(all, evenMod5, l(0, 15, 20)), false);
        assertN("all (empty)", bind(all, evenMod5, l()), true);
        assertN("any (true)", bind(any, evenMod5, l(5, 10, 15)), true);
        assertN("any (false)", bind(any, evenMod5, l(5, 15, 25)), false);
        assertN("any (empty)", bind(any, evenMod5, l()), false);
        assertN("sum", bind(sum, l(1, 2, 3, 4, 32)), 42);
        assertN("product", bind(product, l(1, 2, 3, 7)), 42);
        assertN("maximum", bind(maximum, l(1, 2, 3, 42, 69, 1337)), 1337);
        assertN("minimum", bind(minimum, l(1, 2, 3, 42, 69, 1337)), 1);
    }

};

template <template <class...> class C> struct sublist_extract {

    void operator()(void) const {
        using namespace functional::list;
        using std::bind;
        using std::make_tuple;

        container_builder<C> l;

        assertN("take", bind(take, 3, l(1, 2, 3, 4, 5)), l(1, 2, 3));
        assertN("take (more)", bind(take, 5, l(1, 2, 3)), l(1, 2, 3));
        assertN("take (0)", bind(take, 0, l(1, 2, 3, 4, 5)), l());
        assertN("take (empty)", bind(take, 42, l()), l());
        assertN("drop", bind(drop, 3, l(1, 2, 3, 4, 5)), l(4, 5));
        assertN("drop (more)", bind(drop, 5, l(1, 2, 3)), l());
        assertN("drop (0)", bind(drop, 0, l(1, 2, 3, 4, 5)), l(1, 2, 3, 4, 5));
        assertN("drop (empty)", bind(drop, 42, l()), l());
        assertN("splitAt", bind(split_at, 3, l(1, 2, 3, 4, 5)), make_tuple(l(1, 2, 3), l(4, 5)));
        assertN("splitAt (more)", bind(split_at, 5, l(1, 2, 3)), make_tuple(l(1, 2, 3), l()));
        assertN("splitAt (0)", bind(split_at, 0, l(1, 2, 3)), make_tuple(l(), l(1, 2, 3)));
        assertN("splitAt (empty)", bind(split_at, 42, l()), make_tuple(l(), l()));
        auto below42 = [](auto a) { return a < 42; };
        assertN("takeWhile", bind(take_while, below42, l(1, 2, 3, 42, 1337)), l(1, 2, 3));
        assertN("takeWhile (more)", bind(take_while, below42, l(1, 2, 3)), l(1, 2, 3));
        assertN("takeWhile (0)", bind(take_while, below42, l(42, 69, 1337)), l());
        assertN("takeWhile (empty)", bind(take_while, below42, l()), l());
    }

};


void test_list_basic(void)
{
    using std::vector;
    using std::deque;
    using std::list;
    using std::forward_list;

    test<basic>::with<vector, deque, list, forward_list>();
}

void test_list_transform(void)
{
    using std::vector;
    using std::deque;
    using std::list;
    using std::forward_list;

    test<transform>::with<vector, deque, list, forward_list>();
}

void test_list_fold_reduce(void)
{
    using std::vector;
    using std::deque;
    using std::list;
    using std::forward_list;

    test<fold_reduce>::with<vector, deque, list, forward_list>();
}

void test_list_fold_special(void)
{
    using std::vector;
    using std::deque;
    using std::list;
    using std::forward_list;

    test<fold_special>::with<vector, deque, list, forward_list>();
}

void test_list_sublist_extract(void)
{
    using std::vector;
    using std::deque;
    using std::list;
    using std::forward_list;

    test<sublist_extract>::with<vector, deque, list, forward_list>();
}

void test_list_sublist_predicate(void)
{

}

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
