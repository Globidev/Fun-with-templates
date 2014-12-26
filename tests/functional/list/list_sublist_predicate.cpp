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
        test(is_suffix_of, l(3, 4, 5), l(1, 2, 3, 4, 5)) >> true;
        test(is_suffix_of, l(1, 2, 3), l(1, 2, 3)      ) >> true;
        test(is_suffix_of, l(1, 2, 3), l(1, 2)         ) >> false;
        test(is_suffix_of, l(1, 2, 3), l()             ) >> false;
        test(is_suffix_of, l(),        l(1, 2, 3)      ) >> true;
        test(is_suffix_of, l(),        l()             ) >> true;
        test(is_infix_of,  l(1, 2, 3), l(0, 1, 2, 3, 4)) >> true;
        test(is_infix_of,  l(1, 2, 3), l(1, 2, 3, 4, 5)) >> true;
        test(is_infix_of,  l(1, 2, 3), l(4, 0, 1, 2, 3)) >> true;
        test(is_infix_of,  l(1, 2, 3), l(1, 2, 0, 3, 4)) >> false;
        test(is_infix_of,  l(1, 2, 3), l(4, 1, 2, 0, 3)) >> false;
        test(is_infix_of,  l(),        l(1, 2, 3)      ) >> true;
        test(is_infix_of,  l(),        l()             ) >> true;
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
