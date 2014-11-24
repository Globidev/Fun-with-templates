#pragma once

#include <utility>
#include <type_traits>

namespace tools {
    namespace compile_time {

        using std::enable_if;

        template <
            int i, int e,
            template <int, int...> class F,
            int... ns,
            class... Ts,
            class = typename enable_if<i >= e>::type
        >
        constexpr void for_(Ts &&...) { }

        template <
            int i, int e,
            template <int, int...> class F,
            int... ns,
            class... Ts,
            class = typename enable_if<i < e>::type,
            class = void
        >
        constexpr void for_(Ts &&... ts) {
            using std::forward;

            F<i, ns...> f;
            f(forward<Ts>(ts)...);
            for_<i + 1, e, F, ns...>(forward<Ts>(ts)...);
        }

    };
};
