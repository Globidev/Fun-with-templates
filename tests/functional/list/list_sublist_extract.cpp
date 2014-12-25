#include "test_base.hpp"

#include "functional/maybe.hpp"

template <template <class...> class C> struct sublist_extract {

    void operator()(void) const {
        using namespace functional::maybe;
        container_builder<C> l;
        tuple_builder t;

        auto below42 = [](auto a) { return a < 42; };

        test(take,           3,       l(1, 2, 3, 4, 5)    ) >> l(1, 2, 3);
        test(take,           5,       l(1, 2, 3)          ) >> l(1, 2, 3);
        test(take,           0,       l(1, 2, 3, 4, 5)    ) >> l();
        test(take,           42,      l()                 ) >> l();
        test(drop,           3,       l(1, 2, 3, 4, 5)    ) >> l(4, 5);
        test(drop,           5,       l(1, 2, 3)          ) >> l();
        test(drop,           0,       l(1, 2, 3, 4, 5)    ) >> l(1, 2, 3, 4, 5);
        test(drop,           42,      l()                 ) >> l();
        test(split_at,       3,       l(1, 2, 3, 4, 5)    ) >> t(l(1, 2, 3), l(4, 5));
        test(split_at,       5,       l(1, 2, 3)          ) >> t(l(1, 2, 3), l());
        test(split_at,       0,       l(1, 2, 3)          ) >> t(l(), l(1, 2, 3));
        test(split_at,       42,      l()                 ) >> t(l(), l());
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
        test(span,           below42, l(1, 2, 3, 42, 1337)) >> t(l(1, 2, 3), l(42, 1337));
        test(span,           below42, l(1, 2, 3)          ) >> t(l(1, 2, 3), l());
        test(span,           below42, l(42, 69, 1337)     ) >> t(l(), l(42, 69, 1337));
        test(span,           below42, l()                 ) >> t(l(), l());
        test(break_,         below42, l(42, 1337, 1, 2, 3)) >> t(l(42, 1337), l(1, 2, 3));
        test(break_,         below42, l(42, 69, 1337)     ) >> t(l(42, 69, 1337), l());
        test(break_,         below42, l(1, 2, 3)          ) >> t(l(), l(1, 2, 3));
        test(break_,         below42, l()                 ) >> t(l(), l());
        test(strip_prefix,   l(1, 2), l(1, 2, 3)          ) >> just(l(3));
        test(strip_prefix,   l(1, 2), l(1, 3, 4)          ) >> nothing<C<int>>;
        test(strip_prefix,   l(),     l(1, 2, 3)          ) >> just(l(1, 2, 3));
        test(strip_prefix,   l(1, 2), l()                 ) >> nothing<C<int>>;
        test(strip_prefix,   l(1, 2), l(1, 2)             ) >> just(l());
        test(group,          l(1, 2, 3)                   ) >> l(l(1), l(2), l(3));
        test(group,          l(1, 2, 2, 3, 3, 4, 5, 5, 6) ) >> l(l(1), l(2, 2), l(3, 3), l(4), l(5, 5), l(6));
        test(group,          l(1, 1, 1, 1, 1)             ) >> l(l(1, 1, 1, 1, 1));
        test(group,          l()                          ) >> C<C<int>> { };
        test(inits,          l(1, 2, 3)                   ) >> l(l(), l(1), l(1, 2), l(1, 2, 3));
        test(inits,          l()                          ) >> l(l());
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
