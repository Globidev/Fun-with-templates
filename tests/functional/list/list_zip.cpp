#include "test_base.hpp"

template <template <class...> class C> struct zips {

    void operator()(void) const {
        container_builder<C> l;
        tuple_builder t;
        using namespace std::string_literals;
        using namespace std::chrono_literals;

        test(zip, l(1, 2, 3), l('a', 'b', 'c')             ) >> l(t(1, 'a'), t(2, 'b'), t(3, 'c'));
        test(zip, l(1),       l('a', 'b', 'c')             ) >> l(t(1, 'a'));
        test(zip, C<int>{},   l(1.1, 2.2, 3.3)             ) >> C<std::tuple<int, double>>{};
        test(zip, l(1, 2),    l('a', 'b'),      l(1.1, 2.2)) >> l(t(1, 'a', 1.1), t(2, 'b', 2.2));
        test(zip, l(1, 2),    l('a', 'b', 'c'), l(1.1, 2.2),
                  l(1u, 2u),  l('z', 'y', 'x'), l(.42, .69),
                  l(1337ul),  l('m', 'n', 'o'), l("abcde"s),
                  l(4h, 6h),  l('l', 'o', 'l'), l(1s, 2s)  ) >> l(t(1, 'a', 1.1, 1u, 'z', .42, 1337ul, 'm', "abcde"s, 4h, 'l', 1s));
    }

};

void test_list_zip(void)
{
    run_test<zips>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
