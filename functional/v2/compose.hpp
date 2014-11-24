#pragma once

#include <tuple>
#include <utility>
#include <type_traits>

namespace functional {
    namespace v2 {

        using std::tuple;
        using std::forward;
        using std::enable_if;
        using std::result_of;

        template <
            int n,
            class... Fn,
            class... Tn,
            class enabler = typename enable_if<n == 1>::type
        >
        auto rfold_functors_impl(const tuple<Fn...> & functors, Tn &&... tn)
        -> decltype(std::get<sizeof...(Fn) - n>(functors)(forward<Tn>(tn)...))
        {
            return std::get<sizeof...(Fn) - n>(functors)(forward<Tn>(tn)...);
        }

        template <
            int n,
            class... Fn,
            class... Tn,
            class enabler = typename enable_if<n >= 2>::type
        >
        auto rfold_functors_impl(const tuple<Fn...> & functors, Tn &&... tn)
        {
            return std::get<sizeof...(Fn) - n>(functors)(
                rfold_functors_impl<n - 1>(functors, forward<Tn>(tn)...)
            );
        }

        template <class... Fn, class... Tn, int n = sizeof...(Fn)>
        auto rfold_functors(const tuple<Fn...> & functors, Tn &&... tn)
        {
            return rfold_functors_impl<n>(functors, forward<Tn>(tn)...);
        }

        template <class... Fn> struct composition {

            composition(Fn &&... fn): functors(forward<Fn>(fn)...) {}

            template <class... Tn>
            auto operator()(Tn &&... tn) {
                return rfold_functors(functors, forward<Tn>(tn)...);
            }

            tuple<Fn...> functors;

        };

        template <class... Fn>
        auto compose(Fn &&... fn)
        {
            return composition<Fn...> { fn... };
        }

    };
};
