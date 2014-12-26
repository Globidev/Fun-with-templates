#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _is_prefix_of: composable<2, _is_prefix_of> {

            template <class C>
            auto operator()(const C & p, const C & c) const {
                auto p_it = p.begin();
                auto c_it = c.begin();

                while (p_it != p.end())
                {
                    if (c_it == c.end() || *p_it != *c_it)
                        return false;
                    ++c_it;
                    ++p_it;
                }

                return true;
            }

        } is_prefix_of;

    }
}
