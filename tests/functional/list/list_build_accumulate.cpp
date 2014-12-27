#include "test_base.hpp"

template <template <class...> class C> struct build_accumulate {

    void operator()(void) const {
        tuple_builder t;
        container_builder<C> l;

        auto something = [&t](auto a, auto b) { return t(a+1, b+a); };
        test(map_accum_l, something, 0, l(1, 2, 3)) >> t(3, l(1, 3, 5));
        test(map_accum_r, something, 0, l(1, 2, 3)) >> t(3, l(3, 3, 3));
    }

};

void test_list_build_accumulate(void)
{
    run_test<build_accumulate>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
