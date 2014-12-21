#pragma once

#include <tuple>
#include <utility>

namespace functional {
    namespace list {

        static struct _unzip {

            template <
                template <class...> class C,
                class T1,
                class T2,
                class... Tn
            >
            auto operator()(const C<std::tuple<T1, T2, Tn...>> & c) const {
                using sequence = std::make_index_sequence<2 + sizeof...(Tn)>;

                return helper(sequence{}, c);
            }

        private:

            template <
                size_t... indexes,
                template <class...> class C,
                class Tuple
            >
            static inline auto helper(const std::index_sequence<indexes...> &,
                                      const C<Tuple> & c) {
                return std::make_tuple(unzip_one<indexes>(c)...);
            }

            template <
                size_t i,
                template <class...> class C,
                class Tuple
            >
            static inline auto unzip_one(const C<Tuple> & c) {
                using std::distance;
                using R = typename std::tuple_element<i, Tuple>::type;

                C<R> r(distance(c.begin(), c.end()));

                auto out_it = r.begin();
                for (auto it = c.begin(); it != c.end(); ++it)
                    *out_it++ = std::get<i>(*it);

                return r;
            }

        } unzip;

    }
}
