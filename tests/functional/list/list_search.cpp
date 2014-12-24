#include "test_base.hpp"

#include "functional/maybe.hpp"

template <template <class...> class C> struct search {

    void operator()(void) const {
        using namespace functional::maybe;
        container_builder<C> l;
        tuple_builder t;

        auto even = [](const auto & v) { return v % 2 == 0; };
        auto eq42 = [](const auto & v) { return v == 42; };

        test(elem,      1,    l(1, 2, 3)                ) >> true;
        test(elem,      42,   l(1, 2, 3)                ) >> false;
        test(elem,      42,   l()                       ) >> false;
        test(not_elem,  1,    l(1, 2, 3)                ) >> false;
        test(not_elem,  42,   l(1, 2, 3)                ) >> true;
        test(not_elem,  42,   l()                       ) >> true;
        test(lookup,    3,    l(t(1, 2), t(3, 4))       ) >> just(4);
        test(lookup,    0,    l(t(1, 2), t(3, 4))       ) >> nothing<int>;
        test(lookup,    42,   l(t(42, 1337), t(42, 123))) >> just(1337);
        test(find,      even, l(1, 2, 3)                ) >> just(2);
        test(find,      even, l(1, 69, 1337)            ) >> nothing<int>;
        test(find,      eq42, l(1, 42, 1337)            ) >> just(42);
        test(find,      eq42, l()                       ) >> nothing<int>;
        test(filter,    even, l(1, 2, 3, 4, 5, 6)       ) >> l(2, 4, 6);
        test(filter,    even, l(1, 3, 5, 69, 1337)      ) >> l();
        test(filter,    eq42, l(1, 42, 2, 42, 3)        ) >> l(42, 42);
        test(filter,    eq42, l(1, 2, 3, 69, 1337)      ) >> l();
        test(partition, even, l(1, 2, 3, 4, 5, 6)       ) >> t(l(2, 4, 6), l(1, 3, 5));
        test(partition, even, l(1, 3, 5)                ) >> t(l(), l(1, 3, 5));
        test(partition, eq42, l(1, 42, 2, 42, 3)        ) >> t(l(42, 42), l(1, 2, 3));
        test(partition, eq42, l()                       ) >> t(l(), l());
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
