#pragma once

#include <tuple>

#include "tools/min.hpp"

namespace functional {
    namespace list {

        // This is a variadic zip function so we cannot make it "variadically"
        // composable
        static struct _zip {

            template <
                template <class...> class C,
                class T1,
                class T2,
                class... Tn
            >
            auto operator()(const C<T1> & c1, const C<T2> & c2,
                            const C<Tn> &... cn) const {
                using std::distance;
                using tools::min;
                using R = std::tuple<T1, T2, Tn...>;

                auto size = min(
                    distance(c1.begin(), c1.end()),
                    distance(c2.begin(), c2.end()),
                    distance(cn.begin(), cn.end())...
                );
                C<R> r(size);

                traverse_helper(
                    size,
                    r.begin(),
                    c1.begin(), c2.begin(), cn.begin()...
                );

                return (r);
            }

        private:

            template <class T, class OutputIt, class... InputIts>
            static inline void traverse_helper(T t, OutputIt out,
                                               InputIts... ins) {
                using std::make_tuple;

                if (t)
                {
                    *out++ = make_tuple(*ins++...);
                    traverse_helper(t - 1, out, ins...);
                }
            }

        } zip;

    }
}
