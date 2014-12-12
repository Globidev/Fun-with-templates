#pragma once

#include "maybe_t.hpp"

#include "../compose.hpp"

namespace functional {
    namespace maybe {

        static struct _from_maybe: composable<2, _from_maybe> {

            template <class T>
            auto operator()(const T & def_r, const maybe_t<T> & mb) const {
                return mb.visit([](auto val) { return val; }, def_r);
            }

        } from_maybe;

    }
}
