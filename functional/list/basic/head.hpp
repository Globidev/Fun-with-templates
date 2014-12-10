#pragma once

#include <stdexcept>

#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _head: composable<1, _head> {

            template <class C>
            auto operator()(const C & c) const {
                using std::out_of_range;

                if (c.empty())
                    throw out_of_range(__func__);

                return c.front();
            }

        } head;

    }
}
