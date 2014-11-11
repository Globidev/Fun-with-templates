#pragma once

#include <type_traits>

namespace type_traits {

    using std::is_same;

    template <
        class Tref,
        class T1,
        class... Ts
    > struct is_either {
        static constexpr bool value =
            is_either<Tref, T1>::value ||
            is_either<Tref, Ts...>::value;
    };

    template <
        class Tref,
        class T1
    > struct is_either<Tref, T1> {
        static constexpr bool value = is_same<Tref, T1>::value;
    };

};
