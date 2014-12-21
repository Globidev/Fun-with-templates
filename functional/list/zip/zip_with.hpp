#pragma once

#include "tools/min.hpp"

namespace functional {
    namespace list {

        static struct _zip_with {

            template <
                class F,
                template <class...> class C,
                class T1,
                class T2,
                class... Tn
            >
            auto operator()(const F & f, const C<T1> & c1, const C<T2> & c2,
                            const C<Tn> &... cn) const {
                using std::distance;
                using tools::min;
                using R = typename std::result_of<F(T1, T2, Tn...)>::type;

                auto size = min(
                    distance(c1.begin(), c1.end()),
                    distance(c2.begin(), c2.end()),
                    distance(cn.begin(), cn.end())...
                );
                C<R> r(size);

                traverse_helper(
                    size,
                    f,
                    r.begin(),
                    c1.begin(), c2.begin(), cn.begin()...
                );

                return r;
            }

        private:

            template <class T, class F, class OutputIt, class... InputIts>
            static inline void traverse_helper(T t, const F & f, OutputIt out,
                                               InputIts... ins) {
                if (t)
                {
                    *out++ = f(*ins++...);
                    traverse_helper(t - 1, f, out, ins...);
                }
            }

        } zip_with;

    }
}
