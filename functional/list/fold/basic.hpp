#pragma once

namespace functional {
    namespace list {

        template <class F> struct foldl1 {

            template <class C>
            auto operator()(const C & c) const {
                using std::out_of_range;
                using std::accumulate;

                if (c.empty())
                    throw out_of_range(__func__);

                return accumulate(c.begin() + 1, c.end(), *c.begin(), F{});
            }

        };

        namespace impl {

            template <class F>
            struct foldl1<F> foldl1;

        };
    };
};
