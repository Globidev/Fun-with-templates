#pragma once

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
                    using std::result_of;
                    using Tr = typename result_of<F(T)>::type;

                    C<Tr, n> r;

                    map_impl<n - 1>(f, r, c);

                    return r;
                }

            private:

                template <
                    size_t i,
                    class F,
                    template <class, size_t> class C,
                    class Tr,
                    class T,
                    size_t n,
                    class = typename std::enable_if<i == 0, void>::type
                >
                constexpr void map_impl(const F & f, C<Tr, n> & r,
                                        const C<T, n> & c) const {
                    std::get<i>(r) = f(std::get<i>(c));
                }

                template <
                    size_t i,
                    class F,
                    template <class, size_t> class C,
                    class Tr,
                    class T,
                    size_t n,
                    class = typename std::enable_if<i != 0, void>::type,
                    class = void
                >
                constexpr void map_impl(const F & f, C<Tr, n> & r,
                                        const C<T, n> & c) const {
                    std::get<i>(r) = f(std::get<i>(c));
                    map_impl<i - 1>(f, r, c);
                }

            } map;

        };
    };
};
