#pragma once

#include <algorithm>
#include <stdexcept>

#include "iterator_traits.hpp"

namespace functional {
    namespace v2 {
        namespace list {

            using namespace iterator_traits;

            struct {

                template <class C>
                auto operator()(const C & c1, const C & c2) const {
                    using std::distance;
                    using std::copy;

                    auto c1_size = distance(c1.begin(), c1.end());
                    auto c2_size = distance(c2.begin(), c2.end());
                    C r(c1_size + c2_size);

                    auto end = copy(c1.begin(), c1.end(), r.begin());
                    copy(c2.begin(), c2.end(), end);

                    return r;
                }

            } append;

            struct {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return c.front();
                }

            } head;

            struct {

                template <
                    class C,
                    class enabler = enable_for<C, bidirectional, random_access>
                >
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return c.back();
                }

                template <
                    class C,
                    class enabler = enable_for<C, forward, input>,
                    class = void
                >
                auto operator()(const C & c) const {
                    using std::out_of_range;
                    using std::distance;
                    using std::advance;

                    if (c.empty())
                        throw out_of_range(__func__);

                    auto it = c.begin();
                    advance(it, distance(c.begin(), c.end()) - 1);

                    return *it;
                }

            } last;

            struct {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;
                    using std::next;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return C { next(c.begin()), c.end() };
                }

            } tail;

            struct {

                template <
                    class C,
                    class enabler = enable_for<C, bidirectional, random_access>
                >
                auto operator()(const C & c) const {
                    using std::out_of_range;
                    using std::prev;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return C { c.begin(), prev(c.end()) };
                }

                template <
                    class C,
                    class enabler = enable_for<C, forward, input>,
                    class = void
                >
                auto operator()(const C & c) const {
                    using std::out_of_range;
                    using std::distance;
                    using std::advance;

                    if (c.empty())
                        throw out_of_range(__func__);

                    auto it = c.begin();
                    advance(it, distance(c.begin(), c.end()) - 1);

                    return C { c.cbegin(), it };
                }

            } init;

            struct {

                template <class C>
                auto operator()(const C & c) const {
                    return c.empty();
                }

            } null;

            struct {

                template <class C>
                auto operator()(const C & c) const {
                    using std::distance;

                    return distance(c.begin(), c.end());
                }

            } length;

        };
    };
};
