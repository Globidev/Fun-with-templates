#include <algorithm>

#include "benchmark.hpp"

#include "functional/compose.hpp"
#include "functional/operators.hpp"
#include "functional/list.hpp"

static auto functional_compose(const std::vector<double> & v)
{
    using functional::compose;
    using functional::plus;
    using functional::minimum;

    return compose<plus<3>::f, minimum>(v);
}

static auto iterative_compose(const std::vector<double> & v)
{
    return 3 + *std::min_element(v.begin(), v.end());
}

void test_compose(void)
{
    std::vector<double> v { 10, 5, 8.3, 7, 12.9, 42, 1337, 0, 4.9 };

    benchmark<0xffffff>("Iterative compose", iterative_compose, v);
    benchmark<0xffffff>("Functional compose", functional_compose, v);
}
