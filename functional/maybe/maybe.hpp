#pragma once

#include <type_traits>

#include "maybe_t.hpp"

#include "../compose.hpp"

namespace functional {
    namespace maybe {

        static struct _maybe: composable<3, _maybe> {

            template <
                class T,
                class F,
                class R = typename std::result_of<F(T)>::type
            >
            auto operator()(const R & def_r, const F & f,
                            const maybe_t<T> & mb) const {
                return mb.visit(f, def_r);
            }

        } maybe;

    }
}
