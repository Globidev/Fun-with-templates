#pragma once

#include <functional>

template <
    int n,
    class T,
    template <class...> class F1,
    template <class...> class ... Fn
>
struct RFoldResultOf
{
    using Rp = typename RFoldResultOf<n - 1, T, Fn...>::R;
    using R = typename std::result_of<F1<Rp>(Rp)>::type;
};

template <
    class T,
    template <class...> class F1,
    template <class...> class ... Fn
>
struct RFoldResultOf<1, T, F1, Fn...>
{
    using R = typename std::result_of<F1<T>(T)>::type;
};

template <template <class...> class... Fn>
struct Last
{
    template <
        int n,
        template <class...> class Fh,
        template <class...> class... Fs
    >
    struct LastHelper
    {
        template <class... T>
        using type = typename LastHelper<n - 1, Fs...>::template type<T...>;
    };

    template <
        template <class...> class Fh,
        template <class...> class... Fs
    >
    struct LastHelper<1, Fh, Fs...>
    {
        template <class... T>
        using type = Fh<T...>;
    };

    template <class... T>
    using type = typename LastHelper<sizeof...(Fn), Fn...>::template type<T...>;
};
