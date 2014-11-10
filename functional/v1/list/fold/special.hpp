#pragma once

#include "basic.hpp"

namespace functional {
    namespace v1 {
        namespace list {

            struct concat {

                template <class C, template <class...> class CC>
                auto operator()(const CC<C> & cc) const {
                    return foldl1<append>()(cc);
                }

            };

            struct minimum {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;
                    using std::min_element;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return *min_element(c.begin(), c.end());
                }

            };

            namespace impl {

                struct concat concat;
                struct minimum minimum;

            };
        };
    };
};
