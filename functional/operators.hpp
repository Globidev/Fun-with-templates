#pragma once

namespace functional {
    namespace operators{
        namespace unary {
            namespace unspecialised {

                template <int n> struct _plus {
                    template <class T> struct _impl {

                        auto operator()(const T & t) {
                            return t + n;
                        }

                    };
                };

                template <int n, class T>
                using plus = typename _plus<n>::template _impl<T>;

                template <int n> struct _minus {
                    template <class T> struct _impl {

                        auto operator()(const T & t) {
                            return t - n;
                        }

                    };
                };

                template <int n, class T>
                using minus = typename _minus<n>::template _impl<T>;

            };

            namespace specialised {

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
        };

        namespace binary {
            namespace unspecialised {

                template <class T1, class T2 = T1> struct plus {

                    auto operator()(const T1 & t1, const T2 & t2) {
                        return t1 + t2;
                    }

                };

                template <class T1, class T2 = T1> struct minus {

                    auto operator()(const T1 & t1, const T2 & t2) {
                        return t1 - t2;
                    }

                };

            };

            namespace specialised {

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
};
