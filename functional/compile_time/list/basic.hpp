#pragma once

#include "tools/compile_time/static_for.hpp"

namespace functional {
    namespace compile_time {
        namespace list {

            template <int i, int di = 0> struct copy_one {

                template<
                    template <class, size_t> class C,
                    class T,
                    size_t n_to,
                    size_t n_from
                >
                constexpr void operator()(C<T, n_to> & to,
                                          const C<T, n_from> & from) const {
                    std::get<i>(to) = std::get<i + di>(from);
                }

            };

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n1,
                    size_t n2
                >
                constexpr auto operator()(const C<T, n1> & c1,
                                          const C<T, n2> & c2) const {
                    using tools::compile_time::for_;

                    C<T, n1 + n2> r;

                    for_<0, n1, copy_one>(r, c1);
                    for_<n1, n1 + n2, copy_one, -static_cast<int>(n1)>(r, c2);

                    return r;
                }

            } append;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const C<T, n> & c) const {
                    static_assert(n > 0, "Cannot get head of empty container");
                    return std::get<0>(c);
                }

            } head;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const C<T, n> & c) const {
                    static_assert(n > 0, "Cannot get last of empty container");
                    return std::get<n - 1>(c);
                }

            } last;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const C<T, n> & c) const {
                    static_assert(n > 0, "Cannot get tail of empty container");

                    using tools::compile_time::for_;

                    C<T, n - 1> r;

                    for_<0, n - 1, copy_one, 1>(r, c);
                    // copy_impl<0, n - 1, 1>(r, c);

                    return r;
                }

            } tail;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const C<T, n> & c) const {
                    static_assert(n > 0, "Cannot get init of empty container");

                    using tools::compile_time::for_;

                    C<T, n - 1> r;

                    for_<0, n - 1, copy_one>(r, c);

                    return r;
                }

            } init;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const C<T, n> &) const {
                    return n == 0;
                }

            } null;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const C<T, n> &) const {
                    return n;
                }

            } length;

        };
    };
};
