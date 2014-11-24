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

        };
    };
};
