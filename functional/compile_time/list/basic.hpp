#pragma once

namespace functional {
    namespace compile_time {
        namespace list {

            template <
                size_t i_to,
                size_t i_from,
                size_t di = 0,
                template <class, size_t> class C,
                class T,
                size_t n_to,
                size_t n_from,
                class = typename std::enable_if<i_from == 1, void>::type
            >
            constexpr void copy_impl(C<T, n_to> & to,
                                const C<T, n_from> & from) {
                std::get<i_to>(to) = std::get<n_from - i_from - di>(from);
            }

            template <
                size_t i_to,
                size_t i_from,
                size_t di = 0,
                template <class, size_t> class C,
                class T,
                size_t n_to,
                size_t n_from,
                class = typename std::enable_if<i_from != 1, void>::type,
                class = void
            >
            constexpr void copy_impl(C<T, n_to> & to,
                                const C<T, n_from> & from) {
                std::get<i_to>(to) = std::get<n_from - i_from - di>(from);
                copy_impl<i_to + 1, i_from - 1, di>(to, from);
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
                    copy_impl<n1, n2>(r, c2);

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

                    copy_impl<0, n - 1>(r, c);

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

                    copy_impl<0, n - 1, 1>(r, c);

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
