#pragma once

namespace functional {
    namespace compile_time {
        namespace list {

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

                    copy<0, n1>(r, c1);
                    copy<n1, n2>(r, c2);

                    return r;
                }

            private:

                template <
                    size_t i_to,
                    size_t i_from,
                    template <class, size_t> class C,
                    class T,
                    size_t n_to,
                    size_t n_from,
                    class = typename std::enable_if<i_from == 1, void>::type
                >
                constexpr void copy(C<T, n_to> & to,
                                    const C<T, n_from> & from) const {
                    std::get<i_to>(to) = std::get<n_from - i_from>(from);
                }

                template <
                    size_t i_to,
                    size_t i_from,
                    template <class, size_t> class C,
                    class T,
                    size_t n_to,
                    size_t n_from,
                    class = typename std::enable_if<i_from != 1, void>::type,
                    class = void
                >
                constexpr void copy(C<T, n_to> & to,
                                    const C<T, n_from> & from) const {
                    std::get<i_to>(to) = std::get<n_from - i_from>(from);
                    copy<i_to + 1, i_from - 1>(to, from);
                }

            } append;

        };
    };
};
