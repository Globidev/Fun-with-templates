#pragma once

namespace functional {

    template <class F>
    auto flip(const F & f)
    {
        return [&f](auto a, auto b) { return f(b, a); };
    }

}
