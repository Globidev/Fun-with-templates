#pragma once

#include <functional>

namespace type_traits {

    template <size_t n>
    struct placeholder { };

};

// Enabling custom placeholders to be used with standard functions
namespace std {

    template <size_t n>
    struct is_placeholder<type_traits::placeholder<n>>:
        integral_constant<size_t, n + 1> { };

};
