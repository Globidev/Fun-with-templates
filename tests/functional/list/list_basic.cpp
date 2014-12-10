#include "test_base.hpp"

template <template <class...> class C> struct basic {

    void operator()(void) const {
        container_builder<C> l;

        test(append, l(1, 2, 3), l(4, 5, 6)) >> l(1, 2, 3, 4, 5, 6);
        test(head,   l(1, 2, 3)            ) >> 1;
        test(last,   l(1, 2, 3)            ) >> 3;
        test(tail,   l(1, 2, 3)            ) >> l(2, 3);
        test(init,   l(1, 2, 3)            ) >> l(1, 2);
        test(null,   l(1, 2, 3)            ) >> false;
        test(null,   l()                   ) >> true;
        test(length, l(1, 2, 3)            ) >> 3;
    }

};

void test_list_basic(void)
{
    run_test<basic>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
