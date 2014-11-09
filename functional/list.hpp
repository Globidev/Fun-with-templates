#pragma once

namespace functional {
    namespace list {

        struct append {

            template <class C>
            auto operator()(const C & c1, const C & c2) {
                using std::copy;

                auto c1_size = c1.size();
                auto c2_size = c2.size();
                C r(c1_size + c2_size);

                copy(c1.begin(), c1.end(), r.begin());
                copy(c2.begin(), c2.end(), r.begin() + c1_size);

                return r;
            }

        };

        struct head {

            template <class C>
            auto operator()(const C & c) {
                using std::out_of_range;

                if (c.empty())
                    throw out_of_range(__func__);

                return *c.begin();
            }

        };

        struct last {

            template <class C>
            auto operator()(const C & c) {
                using std::out_of_range;

                if (c.empty())
                    throw out_of_range(__func__);

                return *c.rbegin();
            }

        };

        struct tail {

            template <class C>
            auto operator()(const C & c) {
                using std::out_of_range;

                if (c.empty())
                    throw out_of_range(__func__);

                return C { c.begin() + 1, c.end() };
            }

        };

        struct init {

            template <class C>
            auto operator()(const C & c) {
                using std::out_of_range;

                if (c.empty())
                    throw out_of_range(__func__);

                return C { c.begin(), c.begin() + c.size() - 1 };
            }

        };

        struct null {

            template <class C>
            auto operator()(const C & c) {
                return c.empty();
            }

        };

        struct length {

            template <class C>
            auto operator()(const C & c) {
                return c.size();
            }

        };

        struct minimum {

            template <class C>
            auto operator()(const C & c) {
                using std::out_of_range;
                using std::min_element;

                if (c.empty())
                    throw out_of_range(__func__);

                return *min_element(c.begin(), c.end());
            }

        };

        template <
            template <class, class> class F
        > struct zip_with {

            template <class V1, class V2, template <class...> class C>
            auto operator()(const C<V1> & c1, const C<V2> & c2) {
                using std::min;
                using std::result_of;
                using Vr = typename result_of<F<V1,V2>(V1, V2)>::type;

                auto min_size = min(c1.size(), c2.size());
                C<Vr> r(min_size);
                F<V1, V2> f;

                for (decltype(min_size) i = 0; i < min_size; ++i)
                    r[i] = f(c1[i], c2[i]);

                return r;
            }

        };

        template <template <class...> class F> struct foldl1 {

            template <class C>
            auto operator()(const C & c) {
                using std::out_of_range;
                using std::accumulate;
                using V = typename C::value_type;

                if (c.empty())
                    throw out_of_range(__func__);

                return accumulate(c.begin() + 1, c.end(), *c.begin(), F<V>{});
            }

        };

        namespace impl {

            struct append append;
            struct head head;
            struct last last;
            struct tail tail;
            struct init init;
            struct null null;
            struct length length;

            struct minimum minimum;

            // Variable templates are only supported in clang for now
            // Waiting for gcc5
            template <template <class, class> class F>
            struct zip_with<F> zip_with;

            template <template <class...> class F>
            struct foldl1<F> foldl1;

        };
    };
};
