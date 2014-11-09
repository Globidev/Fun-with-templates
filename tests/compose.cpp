#include <cassert>
#include <algorithm>

#include "benchmark.hpp"

#include "functional/compose.hpp"
#include "functional/operators.hpp"
#include "functional/list.hpp"

static constexpr size_t ITER_COUNT = 10'000'000;

template <class F, class... Args>
static auto compose_bench(const char * func_name, F && f, Args &&... args)
{
    using std::forward;

    double total = 0.;
    Benchmark<ITER_COUNT> b { func_name };

    for (size_t i = 0; i < ITER_COUNT; ++i)
        total += f(forward<Args>(args)...);

    return total;
}

static auto functional_compose(const std::vector<double> & v)
{
    using functional::compose;
    using functional::list::foldl1;
    using functional::list::zip_with;
    using functional::operators::binary::unspecialised::plus;
    using functional::operators::binary::unspecialised::minus;
    using plus3 = functional::operators::unary::specialised::plus<3>;

    return compose<plus3, foldl1<minus>, zip_with<plus>>(v, v);
}

static auto iterative_compose(const std::vector<double> & v)
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

void test_compose(void)
{
    static std::vector<double> v { 10, 5, 8.3, 7, 12.9, 42, 1337, 1, 4.9 };

    assert(compose_bench("iterative", iterative_compose, v) ==
           compose_bench("functional", functional_compose, v));
}
