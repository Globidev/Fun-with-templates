#include "test_base.hpp"

#include "functional/maybe.hpp"

template <template <class...> class C> struct build_scan {

    void operator()(void) const {
        container_builder<C> l;

        auto plus = [](auto a, auto b) { return a + b; };
        test(scanl, plus, 0, l(1, 2, 3)) >> l(0, 1, 3, 6);
        test(scanl1, plus, l(1, 2, 3)) >> l(1, 3, 6);
        test(scanr, plus, 0, l(1, 2, 3)) >> l(6, 5, 3, 0);
        test(scanr1, plus, l(1, 2, 3)) >> l(6, 5, 3);
    }

};

void test_list_build_scan(void)
{
    run_test<build_scan>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
