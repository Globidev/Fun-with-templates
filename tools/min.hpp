#pragma once

namespace tools {

    template <
        class T1,
        class T2,
        class... Tn,
        class=typename std::enable_if<sizeof...(Tn) == 0>::type
    >
    auto min(const T1 & t1, const T2 & t2)
    {
        return (t1 < t2 ? t1 : t2);
    }

    template <
        class T1,
        class T2,
        class... Tn,
        class=typename std::enable_if<sizeof...(Tn) >= 1>::type,
        class=void
    >
    auto min(const T1 & t1, const T2 & t2, const Tn &... tn)
    {
        return (t1 < t2 ? min(t1, tn...) : min(t2, tn...));
    }

}
