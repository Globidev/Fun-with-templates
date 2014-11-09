#pragma once

namespace functional {

    template <class C> struct minimum {
        typename C::value_type operator()(const C & c) {
            return *std::min_element(c.begin(), c.end());
        };
    };

};
