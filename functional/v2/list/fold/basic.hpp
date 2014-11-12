#pragma once

#include <algorithm>
#include <stdexcept>

#include "../iterator_traits.hpp"

namespace functional {
    namespace v2 {
        namespace list {

            using namespace iterator_traits;

            struct {

                template <class F, class V, class C>
                auto operator()(const F & f, const V & v, const C & c) const {
                    using std::accumulate;

                    return accumulate(c.begin(), c.end(), v, f);
                }

            } foldl;

            struct {

                template <class F, class C>
                auto operator()(const F & f, const C & c) const {
                    using std::out_of_range;
                    using std::next;
                    using std::accumulate;

                    if (c.empty())
                        throw(out_of_range(__func__));

                    return accumulate(next(c.begin()), c.end(), c.front(), f);
                }

            } foldl1;

            struct {

                template <
                    class F,
                    class V,
                    class C,
                    class enabler = enable_for<C, bidirectional, random_access>
                >
                auto operator()(const F & f, const V & v, const C & c) const {
                    using std::accumulate;

                    return accumulate(c.rbegin(), c.rend(), v, f);
                }

                template <
                    class F,
                    class V,
                    class C,
                    class enabler = enable_for<C, forward, input>,
                    class = void
                >
                auto operator()(const F & f, const V & v, const C & c) const {
                    return accumr(f, v, c.begin(), c.end());
                }

            private:

                template <class F, class V, class It>
                auto accumr(const F & f, const V & v,
                            const It & begin, const It & end) const {
                    using std::next;

                    if (begin == end)
                        return v;
                    return f(accumr(f, v, next(begin), end), *begin);
                }

            } foldr;

            struct {

                template <
                    class F,
                    class C,
                    class enabler = enable_for<C, bidirectional, random_access>
                >
                auto operator()(const F & f, const C & c) const {
                    using std::out_of_range;
                    using std::next;
                    using std::accumulate;

                    if (c.empty())
                        throw(out_of_range(__func__));

                    return accumulate(next(c.rbegin()), c.rend(), c.back(), f);
                }

                template <
                    class F,
                    class C,
                    class enabler = enable_for<C, forward, input>,
                    class = void
                >
                auto operator()(const F & f, const C & c) const {
                    return accumr(f, c.begin(), c.end());
                }

            private:

                template <class F, class It>
                auto accumr(const F & f, const It & begin,
                            const It & end) const {
                    using std::next;

                    if (next(begin) == end)
                        return *begin;
                    return f(accumr(f, next(begin), end), *begin);
                }

            } foldr1;

        };
    };
};
