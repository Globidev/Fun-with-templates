#include <cassert>
#include <typeinfo>

#include <vector>
#include <deque>
#include <list>

#include "benchmark.hpp"

#include "functional/v2/list.hpp"

template <template <class...> class C> struct container_builder {

    template <class V, class... Vs>
    auto operator()(const V & v, const Vs &... vs) const {
        return C<V> { v, vs... };
    };
};

static constexpr size_t ITER_COUNT = 1'000'000;

template <template <class...> class C>
void test_basic_for(const char * description)
{
    using namespace functional::v2::list;

    container_builder<C> l;
    Benchmark<ITER_COUNT> b { description };

    for (size_t i = 0; i < ITER_COUNT; ++i)
    {
        assert( (append(l(1, 2, 3), l(4, 5, 6)) == l(1, 2, 3, 4, 5, 6)) );
        assert( (head(l(1, 2, 3)) == 1) );
        assert( (last(l(1, 2, 3)) == 3) );
        assert( (tail(l(1, 2, 3)) == l(2, 3)) );
        assert( (init(l(1, 2, 3)) == l(1, 2)) );
        assert( (null(l(1, 2, 3)) == false) );
        assert( (null(C<int>{}) == true) );
        assert( (length(l(1, 2, 3)) == 3) );
    }
}

template <
    template <class...> class C1,
    template <class...> class C2,
    template <class...> class... Cs,
    class T1, class T2, class... Ts
>
void test_basic_for(T1 t1, T2 t2, Ts... ts)
{
    test_basic_for<C1>(t1);
    test_basic_for<C2, Cs...>(t2, ts...);
}

void test_list_basic(void)
{
    using std::vector;
    using std::deque;
    using std::list;

    test_basic_for<vector, deque, list>("vector", "deque", "list");
}
