#pragma once

#include "is_either.hpp"

namespace type_traits {

    template <class... Params> struct parameter_pack {

        // Find the index of a type in the pack
        template <size_t i, class TRef, class T1, class... Ts>
        struct index_of_t {
            static constexpr auto value =
                std::is_same<TRef, T1>::value ?
                i : index_of_t<i + 1, TRef, Ts...>::value;
        };

        template <size_t i, class TRef, class T>
        struct index_of_t<i, TRef, T> {
            static constexpr auto value = i;
        };

        template <class T> struct index_of {
            static_assert(
                is_either<T, Params...>::value,
                "The given type is not part of the parameter pack"
            );

            static constexpr auto value = index_of_t<0, T, Params...>::value;
        };

        // Find the type with the given index in the pack
        template <size_t i, class T1, class... Ts>
        struct type_at_t {
            using type = typename type_at_t<i - 1, Ts...>::type;
        };

        template <class T, class... Ts>
        struct type_at_t<0, T, Ts...> {
            using type = T;
        };

        template <size_t i> struct type_at {
            static_assert(
                i < sizeof...(Params),
                "The parameter pack is smaller than the given index"
            );
            using type = typename type_at_t<i, Params...>::type;
        };

        // Maximum sizeof of the types
        template <class T1, class... Ts> struct max_size_t {
            static constexpr auto value =
                sizeof(T1) > max_size_t<Ts...>::value ?
                sizeof(T1) : max_size_t<Ts...>::value;
        };

        template <class T> struct max_size_t<T> {
            static constexpr auto value = sizeof(T);
        };

        static constexpr auto max_size = max_size_t<Params...>::value;
    };

}
