#include "test_base.hpp"

#include "functional/maybe.hpp"

template <template <class...> class C> struct index {

    void operator()(void) const {
        container_builder<C> l;
        using S = typename C<int>::size_type;
        using namespace functional::maybe;

        test(at,           l(1, 2, 3),           0                    ) >> 1;
        test(at,           l(1, 2, 3, 42, 1337), 4                    ) >> 1337;
        test(at,           l(1, 2, 3, 42, 1337), 3                    ) >> 42;
        test(elem_index,   42,                   l(1, 2, 3, 42, 1337) ) >> just(S(3));
        test(elem_index,   42,                   l(1, 2, 3)           ) >> nothing<S>;
        test(elem_index,   42,                   l()                  ) >> nothing<S>;
        test(elem_indices, 42,                   l(1, 2, 3, 42, 1337) ) >> l(S(3));
        test(elem_indices, 42,                   l(1, 2, 3)           ) >> C<S>{};
        test(elem_indices, 42,                   l(1, 42, 1337, 42, 1)) >> l(S(1), S(3));
        test(elem_indices, 42,                   l()                  ) >> C<S>{};
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
