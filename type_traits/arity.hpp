#pragma once

namespace type_traits {

    // Functors / Lambdas
    template <class F>
    struct arity_of {

        template <class R, class... Args>
        static constexpr auto arity_helper(R (F::*)(Args...) const) {
            return sizeof...(Args);
        }

        static constexpr auto value = arity_helper(&F::operator());

    };

    // Plain old functions
    template <class R, class... Args>
    struct arity_of<R (Args...)> {

        static constexpr auto value = sizeof...(Args);

    };

    // Plain old function pointers
    template <class R, class... Args>
    struct arity_of<R (*)(Args...)> {

        static constexpr auto value = sizeof...(Args);

    };

};
