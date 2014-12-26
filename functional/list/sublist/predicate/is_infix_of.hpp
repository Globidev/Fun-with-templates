#pragma once

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _is_infix_of: composable<2, _is_infix_of> {

            template <class C>
            auto operator()(const C & i, const C & c) const {
                auto c_it = c.begin();
                auto i_it = i.begin();

                if (i_it == i.end())
                    return true;

                while (c_it != c.end())
                {
                    while (*i_it == *c_it)
                    {
                        ++i_it;
                        ++c_it;
                        if (i_it == i.end())
                            return true;
                        if (c_it == c.end())
                            return false;
                    }
                    i_it = i.begin();
                    ++c_it;
                }

                return false;
            }

        } is_infix_of;

    }
}
