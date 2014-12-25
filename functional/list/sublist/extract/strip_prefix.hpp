#pragma once

#include "../../../compose.hpp"
#include "../../../maybe/maybe_t.hpp"

namespace functional {
    namespace list {

        static struct _strip_prefix: composable<2, _strip_prefix> {

            template <class C>
            auto operator()(const C & p, const C & c) const {
                auto start = c.begin();

                for (auto it = p.begin(); it != p.end(); ++it, ++start)
                    if (start == c.end() || *it != *start)
                        return maybe::nothing<C>;

                return maybe::just(C { start, c.end() });
            }

        } strip_prefix;

    }
}
