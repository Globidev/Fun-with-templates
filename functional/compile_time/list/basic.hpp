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

            template <
                size_t start,
                size_t size,
                int di = 0,
                template <class, size_t> class C,
                class T,
                size_t n_to,
                size_t n_from
            >
            constexpr void copy_impl(C<T, n_to> & to, const C<T, n_from> & from)
            {
                using tools::compile_time::for_;

                for_<start, start + size, copy_one, di>(to, from);
            }

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n1,
                    size_t n2
                >
                constexpr auto operator()(const C<T, n1> & c1,
                                          const C<T, n2> & c2) const {
                    C<T, n1 + n2> r;

                    copy_impl<0, n1>(r, c1);
                    copy_impl<n1, n2, -static_cast<int>(n1)>(r, c2);

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
                    C<T, n - 1> r;

                    copy_impl<0, n - 1, 1>(r, c);

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
                    C<T, n - 1> r;

                    copy_impl<0, n - 1>(r, c);

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
