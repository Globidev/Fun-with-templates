#pragma once

#include <algorithm>

#include "../../compose.hpp"
#include "../../maybe/maybe_t.hpp"

namespace functional {
    namespace list {

        static struct _lookup: composable<2, _lookup> {

            template <class T, class U, template <class...> class C>
            auto operator()(const T & t, const C<std::tuple<T, U>> & c) const {
                using std::find_if;

                auto find_by_fst = [&t](const auto & pair) {
                    return std::get<0>(pair) == t;
                };
                auto found = find_if(c.begin(), c.end(), find_by_fst);

                return found == c.end() ?
                    maybe::nothing<U> :
                    maybe::just(std::get<1>(*found));
            }

        } lookup;

    }
}
