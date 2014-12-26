#include "test_base.hpp"

template <template <class...> class C> struct sublist_predicate {

    void operator()(void) const {
        container_builder<C> l;

        test(is_prefix_of, l(1, 2, 3), l(1, 2, 3, 4, 5)) >> true;
        test(is_prefix_of, l(1, 2, 3), l(1, 2, 3)      ) >> true;
        test(is_prefix_of, l(1, 2, 3), l(1, 2)         ) >> false;
        test(is_prefix_of, l(1, 2, 3), l()             ) >> false;
        test(is_prefix_of, l(),        l(1, 2, 3)      ) >> true;
        test(is_prefix_of, l(),        l()             ) >> true;
    }

};

void test_list_sublist_predicate(void)
{
    run_test<sublist_predicate>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
