#include "test_base.hpp"

template <template <class...> class C> struct search {

    void operator()(void) const {
        container_builder<C> l;

        test(elem,     1,  l(1, 2, 3)) >> true;
        test(elem,     42, l(1, 2, 3)) >> false;
        test(elem,     42, l()       ) >> false;
        test(not_elem, 1,  l(1, 2, 3)) >> false;
        test(not_elem, 42, l(1, 2, 3)) >> true;
        test(not_elem, 42, l()       ) >> true;
    }

};

void test_list_search(void)
{
    run_test<search>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
