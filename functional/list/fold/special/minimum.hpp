#pragma once

#include <algorithm>

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _minimum: composable<1, _minimum> {

            template <class C>
            auto operator()(const C & c) const {
                using std::out_of_range;
                using std::min_element;

                if (c.empty())
                    throw out_of_range(__func__);

                return *min_element(c.begin(), c.end());
            }

        } minimum;

    }
}
