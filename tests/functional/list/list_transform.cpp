#include "test_base.hpp"

template <template <class...> class C> struct transform {

    void operator()(void) const {
        container_builder<C> l;

        auto times_fun = [](auto a) { return a * 1337.42; };

        test(map,         times_fun,  l(42, 1337)        ) >> l(56171.64, 1788130.54);
        test(reverse,     l(1, 2, 3)                     ) >> l(3, 2, 1);
        test(intersperse, 4,          l(1, 2, 3)         ) >> l(1, 4, 2, 4, 3);
        test(intercalate, l(4),       l(l(1), l(2), l(3))) >> l(1, 4, 2, 4, 3);
        test(transpose,   l(l(1, 2, 3), l(4, 5, 6))      ) >> l(l(1, 4), l(2, 5), l(3, 6));
    }

};

void test_list_transform(void)
{
    run_test<transform>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
