#include "test_base.hpp"

template <template <class...> class C> struct sublist_extract {

    void operator()(void) const {
        using std::make_tuple;

        container_builder<C> l;

        auto below42 = [](auto a) { return a < 42; };

        test(take,           3,       l(1, 2, 3, 4, 5)    ) >> l(1, 2, 3);
        test(take,           5,       l(1, 2, 3)          ) >> l(1, 2, 3);
        test(take,           0,       l(1, 2, 3, 4, 5)    ) >> l();
        test(take,           42,      l()                 ) >> l();
        test(drop,           3,       l(1, 2, 3, 4, 5)    ) >> l(4, 5);
        test(drop,           5,       l(1, 2, 3)          ) >> l();
        test(drop,           0,       l(1, 2, 3, 4, 5)    ) >> l(1, 2, 3, 4, 5);
        test(drop,           42,      l()                 ) >> l();
        test(split_at,       3,       l(1, 2, 3, 4, 5)    ) >> make_tuple(l(1, 2, 3), l(4, 5));
        test(split_at,       5,       l(1, 2, 3)          ) >> make_tuple(l(1, 2, 3), l());
        test(split_at,       0,       l(1, 2, 3)          ) >> make_tuple(l(), l(1, 2, 3));
        test(split_at,       42,      l()                 ) >> make_tuple(l(), l());
        test(take_while,     below42, l(1, 2, 3, 42, 1337)) >> l(1, 2, 3);
        test(take_while,     below42, l(1, 2, 3)          ) >> l(1, 2, 3);
        test(take_while,     below42, l(42, 69, 1337)     ) >> l();
        test(take_while,     below42, l()                 ) >> l();
        test(drop_while,     below42, l(1, 2, 3, 42, 1337)) >> l(42, 1337);
        test(drop_while,     below42, l(1, 2, 3)          ) >> l();
        test(drop_while,     below42, l(42, 69, 1337)     ) >> l(42, 69, 1337);
        test(drop_while,     below42, l()                 ) >> l();
        test(drop_while_end, below42, l(42, 1337, 1, 2, 3)) >> l(42, 1337);
        test(drop_while_end, below42, l(1, 2, 3)          ) >> l();
        test(drop_while_end, below42, l(42, 69, 1337)     ) >> l(42, 69, 1337);
        test(drop_while_end, below42, l()                 ) >> l();
        test(span,           below42, l(1, 2, 3, 42, 1337)) >> make_tuple(l(1, 2, 3), l(42, 1337));
        test(span,           below42, l(1, 2, 3)          ) >> make_tuple(l(1, 2, 3), l());
        test(span,           below42, l(42, 69, 1337)     ) >> make_tuple(l(), l(42, 69, 1337));
        test(span,           below42, l()                 ) >> make_tuple(l(), l());
        test(break_,         below42, l(42, 1337, 1, 2, 3)) >> make_tuple(l(42, 1337), l(1, 2, 3));
        test(break_,         below42, l(42, 69, 1337)     ) >> make_tuple(l(42, 69, 1337), l());
        test(break_,         below42, l(1, 2, 3)          ) >> make_tuple(l(), l(1, 2, 3));
        test(break_,         below42, l()                 ) >> make_tuple(l(), l());
    }

};

void test_list_sublist_extract(void)
{
    run_test<sublist_extract>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
