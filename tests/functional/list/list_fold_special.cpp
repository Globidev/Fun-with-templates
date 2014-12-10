#include "test_base.hpp"

template <template <class...> class C> struct fold_special {

    void operator()(void) const {
        container_builder<C> l;

        auto f = [&l](auto x) { return l(x - 1, x, x + 1); };
        auto evenMod5 = [](auto x) { return !(x % 5) && !(x % 2); };

        test(concat,     l(l(1, 2), l(3, 4))                   ) >> l(1, 2, 3, 4);
        test(concat_map, f,                        l(1, 2, 3)  ) >> l(0, 1, 2, 1, 2, 3, 2, 3, 4);
        test(and_,       l(true, true, true)                   ) >> true;
        test(and_,       l(true, false, true)                  ) >> false;
        test(and_,       l()                                   ) >> true;
        test(or_,        l(false, true, false)                 ) >> true;
        test(or_,        l(false, false, false)                ) >> false;
        test(or_,        l()                                   ) >> false;
        test(all,        evenMod5,                 l(0, 10, 20)) >> true;
        test(all,        evenMod5,                 l(0, 15, 20)) >> false;
        test(all,        evenMod5,                 l()         ) >> true;
        test(any,        evenMod5,                 l(5, 10, 15)) >> true;
        test(any,        evenMod5,                 l(5, 15, 25)) >> false;
        test(any,        evenMod5,                 l()         ) >> false;
        test(sum,        l(1, 2, 3, 4, 32)                     ) >> 42;
        test(product,    l(1, 2, 3, 7)                         ) >> 42;
        test(maximum,    l(1, 2, 3, 42, 69, 1337)              ) >> 1337;
        test(minimum,    l(1, 2, 3, 42, 69, 1337)              ) >> 1;
    }

};

void test_list_fold_special(void)
{
    run_test<fold_special>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
