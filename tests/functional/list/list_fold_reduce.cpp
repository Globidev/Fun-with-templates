#include "test_base.hpp"

template <template <class...> class C> struct fold_reduce {

    void operator()(void) const {
        container_builder<C> l;

        auto fold_plus_42 = [](auto r, auto v) { return v + r + 42; };

        test(foldl,  fold_plus_42, 42,             l(1, 2, 3)) >> 174;
        test(foldl1, fold_plus_42, l(42, 1, 2, 3)            ) >> 174;
        test(foldr,  fold_plus_42, 42,             l(1, 2, 3)) >> 174;
        test(foldr1, fold_plus_42, l(42, 1, 2, 3)            ) >> 174;
    }

};

void test_list_fold_reduce(void)
{
    run_test<fold_reduce>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
