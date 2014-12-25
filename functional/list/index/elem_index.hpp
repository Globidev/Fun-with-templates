#pragma once

#include "../../compose.hpp"

#include "../../maybe/maybe_t.hpp"

namespace functional {
    namespace list {

        static struct _elem_index: composable<2, _elem_index> {

            template <class T, template <class...> class C>
            auto operator()(const T & t, const C<T> & c) const {
                using R = typename C<T>::size_type;

                R r { };

                for (auto it = c.begin(); it != c.end(); ++it, ++r)
                    if (*it == t)
                        return maybe::just(r);
                return maybe::nothing<R>;
            }

        } elem_index;

    }
}
