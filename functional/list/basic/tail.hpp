#pragma once

#include <stdexcept>
#include <iterator>

#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _tail: composable<1, _tail> {

            template <class C>
            auto operator()(const C & c) const {
                using std::out_of_range;
                using std::next;

                if (c.empty())
                    throw out_of_range(__func__);

                return C { next(c.begin()), c.end() };
            }

        } tail;

    }
}
