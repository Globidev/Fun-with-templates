#pragma once

#include <array>
#include <utility>

namespace functional {
    namespace compile_time {

        template <class T, size_t n>
        struct array: public std::array<T, n> {

            template <class... Ts>
            constexpr array(Ts &&... ts):
                std::array<T, n> { { std::forward<Ts>(ts)... } } {

            }

            constexpr bool operator==(const array<T, n> & other) const {
                return equals<n - 1>(other);
            }

        private:

            template <
                size_t i,
                class = typename std::enable_if<i == 0>::type
            >
            constexpr bool equals(const array<T, n> & other) const {
                return std::get<i>(*this) == std::get<i>(other);
            }

            template <
                size_t i,
                class = typename std::enable_if<i != 0>::type,
                class = void
            >
            constexpr bool equals(const array<T, n> & other) const {
                return std::get<i>(*this) == std::get<i>(other) &&
                       equals<i - 1>(other);
            }

        };

        template<class T>
        struct array<T, 0>: public std::array<T, 0> {

            constexpr array(): std::array<T, 0>() { }

            constexpr bool operator==(const array<T, 0> &) const {
                return true;
            }

        };

    };
};
