#pragma once

#include "../../compose.hpp"

#include "../../maybe/maybe_t.hpp"

namespace functional {
    namespace list {

        static struct _find_index: composable<2, _find_index> {

            template <class F, class C>
            auto operator()(const F & f, const C & c) const {
                using R = typename C::size_type;

                R r { };

                for (auto it = c.begin(); it != c.end(); ++it, ++r)
                    if (f(*it))
                        return maybe::just(r);
                return maybe::nothing<R>;
            }

        } find_index;

    }
}
