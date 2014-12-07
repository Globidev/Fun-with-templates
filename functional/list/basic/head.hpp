#pragma once

#include <stdexcept>

namespace functional {
    namespace list {

        struct {

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
