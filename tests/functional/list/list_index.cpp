#include "test_base.hpp"

template <template <class...> class C> struct index {

    void operator()(void) const {
        container_builder<C> l;

        test(at, l(1, 2, 3),           0) >> 1;
        test(at, l(1, 2, 3, 42, 1337), 4) >> 1337;
        test(at, l(1, 2, 3, 42, 1337), 3) >> 42;
    }

};

void test_list_index(void)
{
    run_test<index>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
