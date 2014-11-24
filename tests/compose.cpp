#include <cassert>
#include <algorithm>

#include "tools/benchmark.hpp"

#include "functional/v1/compose.hpp"
#include "functional/v1/operators.hpp"
#include "functional/v1/list.hpp"

static constexpr size_t ITER_COUNT = 10'000'000;

template <class F, class... Args>
static auto compose_bench(const char * func_name, F && f, Args &&... args)
{
    using std::forward;

    double total = 0.;
    tools::Benchmark<ITER_COUNT> b { func_name };

    for (size_t i = 0; i < ITER_COUNT; ++i)
        total += f(forward<Args>(args)...);

    return total;
}

static auto functional_compose_v1(const std::vector<double> & v)
{
    using functional::v1::compose;
    using functional::v1::list::foldl1;
    using functional::v1::list::zip_with;
    using functional::v1::operators::binary::plus;
    using functional::v1::operators::binary::minus;
    using plus3 = functional::v1::operators::unary::plus<3>;

    return compose<plus3, foldl1<minus>, zip_with<plus>>(v, v);
}

static auto iterative_compose_v1(const std::vector<double> & v)
{
    using std::out_of_range;
    using std::accumulate;

    if (v.empty())
        throw out_of_range(__func__);

    std::vector<double> zipped(v.size());
    for (size_t i = 0; i < v.size(); ++i)
        zipped[i] = v[i] + v[i];

    auto minus = [](auto a, auto b) { return a - b; };
    return 3 + accumulate(
        zipped.begin() + 1, zipped.end(), *zipped.begin(), minus
    );
}

void test_compose_v1(void)
{
    static std::vector<double> v { 10, 5, 8.3, 7, 12.9, 42, 1337, 1, 4.9 };

    assert(compose_bench("iterative", iterative_compose_v1, v) ==
           compose_bench("functional", functional_compose_v1, v));
}

#include "functional/v2/compose.hpp"

void test_compose_v2(void)
{
    // Note the absence of explicit types here :D

    // using functional::v2::compose;
    // using std::bind;
    // using namespace std::placeholders;
    // using std::ref;

    // auto y = 21;
    // auto plus = [](auto a, auto b) { return a + b; };
    // auto plus_y_value = bind(plus, _1, y);
    // auto plus_y_ref = bind(plus, _1, ref(y));

    // assert(compose(plus_y_value, plus)(12, 9) == 42);
    // y += 1295;
    // assert(compose(plus_y_ref, plus)(12, 9) == 1337);

    // auto magic = [](auto a, auto b, auto c) { return a + b * c; };
    // auto magic_plus_y_both = compose(plus_y_value, plus_y_ref, magic);

    // assert(magic_plus_y_both(-42, 6, 7) == 1337);
    // auto magic_b42_plus_y_both = bind(magic_plus_y_both, _1, 42, _2);
    // assert(magic_b42_plus_y_both(-42, 1) == 1337);
}
