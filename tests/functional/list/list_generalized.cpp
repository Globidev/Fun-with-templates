#include "test_base.hpp"

template <template <class...> class C> struct generalized {

    void operator()(void) const {
        container_builder<C> l;

        auto eq = [](auto a, auto b) { return a == b; };
        auto sup = [](auto a, auto b) { return a > b; };
        test(nub_by,           eq,  l(1, 2, 3, 1, 2, 4, 3, 5)               ) >> l(1, 2, 3, 4, 5);
        test(delete_by,        sup, 3,                      l(1, 2, 3, 4, 3)) >> l(2, 3, 4, 3);
        test(delete_firsts_by, eq,  l(1, 2, 4, 3, 3, 5, 4), l(1, 1, 3, 3, 4)) >> l(2, 5, 4);
    }

};

void test_list_generalized(void)
{
    run_test<generalized>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
