#pragma once

namespace functional {
    namespace list {

        template <template <class> class F> struct map {

            template <class C>
            auto operator()(const C & c) const {
                (void)c;
            }

        };

        namespace impl {

            template <template <class> class F>
            struct map<F> map;

        };
    };
};
