#pragma once

#include "tools/compile_time/static_for.hpp"

namespace functional {
    namespace compile_time {
        namespace list {

            struct {

                template <
                    class F,
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const F & f, const C<T, n> & c) const {
                    using tools::compile_time::for_;
                    using std::result_of;
                    using Tr = typename result_of<F(T)>::type;

                    C<Tr, n> r;

                    for_<0, n, map_impl>(f, r, c);

                    return r;
                }

            private:

                template <int i> struct map_impl {

                    template <
                        class F,
                        template <class, size_t> class C,
                        class Tr,
                        class T,
                        size_t n
                    >
                    constexpr void operator()(const F & f, C<Tr, n> & r,
                                              const C<T, n> & c) const {
                        std::get<i>(r) = f(std::get<i>(c));
                    }

                };

            } map;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n
                >
                constexpr auto operator()(const C<T, n> & c) const {
                    using tools::compile_time::for_;

                    C<T, n> r;

                    for_<0, n, reverse_impl>(r, c);

                    return r;
                }

            private:

                template <int i> struct reverse_impl {

                    template <
                        template <class, size_t> class C,
                        class T,
                        size_t n
                    >
                    constexpr void operator()(C<T, n> & r,
                                              const C<T, n> & c) const {
                        std::get<i>(r) = std::get<n - i - 1>(c);
                    }

                };

            } reverse;

            struct {

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n,
                    class = typename std::enable_if<n <= 1>::type
                >
                constexpr auto operator()(const T &, const C<T, n> & c) const {
                    return c;
                }

                template <
                    template <class, size_t> class C,
                    class T,
                    size_t n,
                    class = typename std::enable_if<n >= 2>::type,
                    class = void
                >
                constexpr auto operator()(const T & t, const C<T, n> & c) const {
                    using tools::compile_time::for_;

                    C<T, n * 2 - 1> r;

                    for_<0, n * 2 - 1, intersperse_impl>(r, t, c);

                    return r;
                }

            private:

                template <
                    int i,
                    template <class, size_t> class C,
                    class T,
                    size_t n_to,
                    size_t n_from,
                    class = typename std::enable_if<i % 2 == 0>::type
                >
                static constexpr void intersperse_impl_f(C<T, n_to> & r, const T &,
                                                         const C<T, n_from> & c) {
                    std::get<i>(r) = std::get<i / 2>(c);
                }

                template <
                    int i,
                    template <class, size_t> class C,
                    class T,
                    size_t n_to,
                    size_t n_from,
                    class = typename std::enable_if<i % 2 != 0>::type,
                    class = void
                >
                static constexpr void intersperse_impl_f(C<T, n_to> & r, const T & t,
                                                         const C<T, n_from> &) {
                    std::get<i>(r) = t;
                }

                template <int i>
                struct intersperse_impl {

                    template <
                        template <class, size_t> class C,
                        class T,
                        size_t n_to,
                        size_t n_from
                    >
                    constexpr void operator()(C<T, n_to> & r, const T & t,
                                              const C<T, n_from> & c) const {
                        intersperse_impl_f<i>(r, t, c);
                    }

                };

            } intersperse;

        };
    };
};
