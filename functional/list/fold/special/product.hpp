#pragma once

#include "../reduce/foldl.hpp"
#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _product: composable<1, _product> {

            template <class C>
            auto operator()(const C & c) const {
                return foldl([](auto a, auto b) { return a * b; }, 1, c);
            }

        } product;

    }
}
