#pragma once

#include <stdexcept>
#include <iterator>

namespace functional {
    namespace list {

        struct {

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
