#pragma once

#include "maybe_t.hpp"

#include "../compose.hpp"

namespace functional {
    namespace maybe {

        static struct _is_just: composable<1, _is_just> {

            template <class T>
            auto operator()(const maybe_t<T> & mb) const {
                return mb.visit([](const T &) { return true; }, false);
            }

        } is_just;

    }
}
