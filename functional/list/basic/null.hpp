#pragma once

namespace functional {
    namespace list {

        struct {

            template <class C>
            auto operator()(const C & c) const {
                return c.empty();
            }

        } null;

    }
}
