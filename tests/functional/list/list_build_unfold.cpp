#include "test_base.hpp"

#include "functional/maybe.hpp"

template <template <class...> class C> struct build_unfold {

    void operator()(void) const {
        using namespace functional::maybe;
        using std::make_tuple;
        container_builder<C> l;

        auto inc_up_to_3 = [](auto a) {
            return a > 3 ? nothing<std::tuple<decltype(a), decltype(a)>> :
                           just(make_tuple(a, a + 1));
        };
        auto build_squared_up_to_1337 = [](auto a) {
            return a > 1337 ? nothing<std::tuple<decltype(a), decltype(a)>>:
                              just(make_tuple(a, a * a));
        };
        test(unfoldr<C>, inc_up_to_3, 1 ) >> l(1, 2, 3);
        test(unfoldr<C>, inc_up_to_3, 42) >> l();
        test(unfoldr<C>, build_squared_up_to_1337, 2) >> l(2, 4, 16, 256);
    }

};

void test_list_build_unfold(void)
{
    run_test<build_unfold>::with<
        vector,
        deque,
        list,
        forward_list
    >();
}
