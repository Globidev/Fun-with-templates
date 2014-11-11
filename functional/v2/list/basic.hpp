#pragma once

#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <type_traits>

namespace functional {
    namespace v2 {
        namespace list {

            using std::enable_if;
            using std::is_base_of;

            // Iterator traits helpers
            using std::iterator_traits;
            using std::bidirectional_iterator_tag;

            template <class C>
            using iterator_category = typename iterator_traits<
                typename C::iterator
            >::iterator_category;

            template <class C, class Btag, class T>
            using enable_for_iterators = typename enable_if<
                is_base_of<Btag, iterator_category<C>>::value, T
            >::type;

            template <class C, class Btag, class T>
            using disable_for_iterators = typename enable_if<
                !is_base_of<Btag, iterator_category<C>>::value, T
            >::type;

            // Impl
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

                template <class C>
                auto operator()(const C & c) const
                    -> enable_for_iterators<
                        C,
                        bidirectional_iterator_tag,
                        typename C::value_type
                    > {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return c.back();
                }

                template <class C>
                auto operator()(const C & c) const
                    -> disable_for_iterators<
                        C,
                        bidirectional_iterator_tag,
                        typename C::value_type
                    > {
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

                template <class C>
                auto operator()(const C & c) const
                    -> enable_for_iterators<
                        C,
                        bidirectional_iterator_tag,
                        C
                    > {
                    using std::out_of_range;
                    using std::prev;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return C { c.begin(), prev(c.end()) };
                }

                template <class C>
                auto operator()(const C & c) const
                    -> disable_for_iterators<
                        C,
                        bidirectional_iterator_tag,
                        C
                    > {
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