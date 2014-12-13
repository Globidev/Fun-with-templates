#pragma once

#include <new>
#include <cstring>
#include <type_traits>

#include "type_traits/is_either.hpp"
#include "type_traits/parameter_pack.hpp"

namespace functional {
    namespace variant {

        template <class T1, class... Ts>
        struct variant_t {

            using pack = type_traits::parameter_pack<T1, Ts...>;
            using union_t = typename std::aligned_storage<pack::max_size>::type;
            using this_t = variant_t<T1, Ts...>;
            using index_t = unsigned char; // Allows a number of types up to 256
                                           // This should be enough :)
            template <class T>
            explicit variant_t(const T & t) {
                using namespace type_traits;
                static_assert(
                    is_either<T, T1, Ts...>::value,
                    "The type is not part of the variant"
                );

                new (&storage) T(t);
                current_type_id = pack::template index_of<T>::value;
            }

            template <class T>
            this_t & operator=(const T & t) {
                using namespace type_traits;
                static_assert(
                    is_either<T, T1, Ts...>::value,
                    "The type is not part of the variant"
                );

                new (&storage) T(t);
                current_type_id = pack::template index_of<T>::value;
                return (*this);
            }

            template <class F>
            auto visit(const F & f) {
                return type_switch(f);
            }

            template <
                class... Fs,
                class = typename std::enable_if<sizeof...(Ts) >= 1>::type
            >
            auto visit(const Fs &... fs) {
                return type_switch_multiple(fs...);
            }

        private:

            template <
                index_t i = 0,
                class F,
                class = typename std::enable_if<i < sizeof...(Ts)>::type
            >
            inline auto type_switch(const F & f)
            {
                if (i == current_type_id)
                    return f(*as<i>());
                return type_switch<i + 1>(f);
            }

            template <
                index_t i = 0,
                class F,
                class = typename std::enable_if<i >= sizeof...(Ts)>::type,
                class = void
            >
            inline auto type_switch(const F & f) {
                return f(*as<i>());
            }

            template <
                index_t i = 0,
                class F,
                class... Fs,
                class = typename std::enable_if<i < sizeof...(Ts)>::type
            >
            inline auto type_switch_multiple(const F & f, const Fs &... fs) {
                if (i == current_type_id)
                    return f(*as<i>());
                return type_switch_multiple<i + 1>(fs...);
            }

            template <
                index_t i,
                class F,
                class = typename std::enable_if<i >= sizeof...(Ts)>::type
            >
            inline auto type_switch_multiple(const F & f) {
                return f(*as<i>());
            }


            template <index_t i>
            auto as() const {
                using T = typename pack::template type_at<i>::type;

                return static_cast<const T *>(
                    static_cast<const void *>(&storage)
                );
            }

            union_t storage;
            index_t current_type_id;

        };

    }
}
