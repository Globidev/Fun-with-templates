#pragma once

#include <algorithm>
#include <stdexcept>

namespace functional {
    namespace v2 {
        namespace list {

            struct {

                template <class C>
                auto operator()(const C & c1, const C & c2) const {
                    using std::copy;

                    C r(c1.size() + c2.size());

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
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return c.back();
                }

            } last;

            struct {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return C { ++c.begin(), c.end() };
                }

            } tail;

            struct {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return C { c.begin(), --c.end() };
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
                    return c.size();
                }

            } length;

        };
    };
};
