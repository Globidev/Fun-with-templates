#pragma once

// There are four sequence containers in the STL
// (I am not counting std::array because it's compile-time only)
#include <vector>
#include <deque>
#include <list>
#include <forward_list> // This one makes some functions hard to implement...

using std::vector;
using std::deque;
using std::list;
using std::forward_list;

#include <iostream>
#include <tuple>
#include <utility>
#include <cassert>

#include "tools/type_name.hpp"
#include "tools/benchmark.hpp"

#include "functional/list.hpp"

using namespace functional::list;

// Each test assertion will be run the following number of times
static constexpr size_t ITER_COUNT = 1'000'000;

// Main test wrapper
template <template <template <class...> class> class TestF> struct run_test {

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

        cout << "Testing: " << pretty_name<TestF<C>>()
             << " (" << ITER_COUNT << " iterations)"
             << endl << endl;
        TestF<C>{}();
        cout << endl << endl;
    }

};

template <class F, class... Ts> struct tester {

    using R = typename std::result_of<F(Ts...)>::type;

    tester(F && f, Ts &&... ts):
        bind_expr_(std::bind(std::forward<F>(f), std::forward<Ts>(ts)...)) { }

    auto operator>>(const R & result) {
        using tools::pretty_name;

        tools::benchmark b { pretty_name<F>() };

        for (size_t i = 0; i < ITER_COUNT; ++i)
            assert( (bind_expr_() == result) );
    }

private:

    std::function<R ()> bind_expr_;

};

template <class F, class... Ts>
auto test(F && f, Ts &&... ts)
{
    using std::forward;

    return tester<F, Ts...> { forward<F>(f), forward<Ts>(ts)... };
};

// For conveniency
template <template <class...> class C> struct container_builder {

    template <class V, class... Vs>
    auto operator()(const V & v, const Vs &... vs) const {
        return C<V> { v, vs... };
    };

    auto operator()(void) const {
        return C<int>{};
    }

};
