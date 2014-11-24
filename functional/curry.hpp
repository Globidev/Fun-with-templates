#pragma once

#include <functional>
#include <utility>

#include "type_traits/placeholders.hpp"
#include "type_traits/sequence.hpp"

namespace functional {
    namespace v2 {

        template <
            class F,
            class... Fs,
            size_t... indexes
        >
        auto curry_impl(F && f, const std::integer_sequence<size_t, indexes...>,
                        Fs &&... fs)
        {
            using std::bind;
            using std::forward;

            return bind(forward<F>(f), forward<Fs>(fs)...,
                        type_traits::placeholder<indexes> {}...);
        }

        template <
            size_t arity,
            int delta_index = 0,
            class F,
            class... Fs
        >
        auto curry(F && f, Fs &&... fs)
        {
            using std::forward;

            auto index_sequence = type_traits::make_range_index_sequence<
                sizeof...(Fs) + delta_index, arity + delta_index
            > { };

            return curry_impl(f, index_sequence, forward<Fs>(fs)...);
        }

    };
};
