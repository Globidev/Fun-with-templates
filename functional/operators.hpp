#pragma once

namespace functional {
    namespace operators{
        namespace unary {

            template <int n> struct plus {

                template <class T>
                auto operator()(const T & t) {
                    return t + n;
                }

            };

            template <int n> struct minus {

                template <class T>
                auto operator()(const T & t) {
                    return t - n;
                }

            };

        };

        namespace binary {

            struct plus {

                template <class T1, class T2 = T1>
                auto operator()(const T1 & t1, const T2 & t2) {
                    return t1 + t2;
                }

            };

            struct minus {

                template <class T1, class T2 = T1>
                auto operator()(const T1 & t1, const T2 & t2) {
                    return t1 - t2;
                }

            };

        };
    };
};
