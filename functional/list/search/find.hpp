#pragma once

#include <algorithm>

#include "../../compose.hpp"
#include "../../maybe/maybe_t.hpp"

namespace functional {
    namespace list {

        static struct _find: composable<2, _find> {

            template <class F, class T, template <class...> class C>
            auto operator()(const F & pred, const C<T> & c) const {
                using std::find_if;

                auto found = find_if(c.begin(), c.end(), pred);

                return found == c.end() ?
                    maybe::nothing<T> :
                    maybe::just(*found);
            }

        } find;

    }
}
