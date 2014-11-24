#pragma once

#include <utility>
#include <type_traits>

namespace tools {
    namespace compile_time {

        using std::enable_if;

        template <
            int i, int e,
            template <int> class F,
            class... Ts,
            class = typename enable_if<i >= e, void>::type
        >
        constexpr void for_(Ts &&...) { }

        template <
            int i, int e,
            template <int> class F,
            class... Ts,
            class = typename enable_if<i < e, void>::type,
            class = void
        >
        constexpr void for_(Ts &&... ts) {
            using std::forward;

            F<i> f;
            f(forward<Ts>(ts)...);
            for_<i + 1, e, F>(forward<Ts>(ts)...);
        }

    };
};
