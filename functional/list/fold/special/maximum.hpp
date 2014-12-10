#pragma once

#include <algorithm>

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _maximum: composable<1, _maximum> {

            template <class C>
            auto operator()(const C & c) const {
                using std::out_of_range;
                using std::max_element;

                if (c.empty())
                    throw out_of_range(__func__);

                return *max_element(c.begin(), c.end());
            }

        } maximum;

    }
}
