#include <cassert>
#include <iostream>
#include <functional>

#include <vector>
#include <deque>
#include <list>
#include <forward_list>

#include "benchmark.hpp"
#include "tools/type_name.hpp"

#include "functional/v2/list.hpp"

static constexpr size_t ITER_COUNT = 10'000'000;

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

        TestF<C> test;

        cout << "Testing: " << pretty_name<TestF<C>>() << endl << endl;
        test();
        cout << endl << endl;
    }

};

template <class F, class T>
auto assertN(const char *description, const F & f, const T & t)
{
    Benchmark<ITER_COUNT> b { description };

    for (size_t i = 0; i < ITER_COUNT; ++i)
        assert( (f() == t) );
}

template <template <class...> class C> struct container_builder {

    template <class V, class... Vs>
    auto operator()(const V & v, const Vs &... vs) const {
        return C<V> { v, vs... };
    };

};


template <template <class...> class C> struct basic {

    void operator()(void) const {
        using namespace functional::v2::list;
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
        using namespace functional::v2::list;
        using std::bind;

        container_builder<C> l;

        auto x = 1337.42;
        auto times_x = [x](auto a) { return a * x; };
        assertN("map", bind(map, times_x, l(42, 1337)), l(56171.64, 1788130.54));
        assertN("reverse", bind(reverse, l(1, 2, 3)), l(3, 2, 1));
        assertN("intersperse", bind(intersperse, 4, l(1, 2, 3)), l(1, 4, 2, 4, 3));
    }

};

template <template <class...> class C> struct fold_basic {

    void operator()(void) const {
        using namespace functional::v2::list;
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
        using namespace functional::v2::list;
        using std::bind;

        container_builder<C> l;

        assertN("concat", bind(concat, l(l(1, 2), l(3, 4))), l(1, 2, 3, 4));
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

void test_list_fold_basic(void)
{
    using std::vector;
    using std::deque;
    using std::list;
    using std::forward_list;

    test<fold_basic>::with<vector, deque, list, forward_list>();
}

void test_list_fold_special(void)
{
    using std::vector;
    using std::deque;
    using std::list;
    using std::forward_list;

    test<fold_special>::with<vector, deque, list, forward_list>();
}
