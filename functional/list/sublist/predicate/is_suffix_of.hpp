#pragma once

#include <iterator>

#include "../../../compose.hpp"

namespace functional {
    namespace list {

        static struct _is_suffix_of: composable<2, _is_suffix_of> {

            template <class C>
            auto operator()(const C & s, const C & c) const {
                using std::distance;
                using std::advance;

                auto s_size = distance(s.begin(), s.end());
                auto c_size = distance(c.begin(), c.end());
                if (s_size > c_size)
                    return false;
                auto s_it = s.begin();
                auto c_it = c.begin();

                advance(c_it, c_size - s_size);
                while (s_it != s.end())
                {
                    if (*s_it != *c_it)
                        return false;
                    ++s_it;
                    ++c_it;
                }

                return true;
            }

        } is_suffix_of;

    }
}
