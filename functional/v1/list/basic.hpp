#pragma once

namespace functional {
    namespace v1 {
        namespace list {

            struct append {

                template <class C>
                auto operator()(const C & c1, const C & c2) const {
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
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return *c.begin();
                }

            };

            struct last {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return *c.rbegin();
                }

            };

            struct tail {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return C { c.begin() + 1, c.end() };
                }

            };

            struct init {

                template <class C>
                auto operator()(const C & c) const {
                    using std::out_of_range;

                    if (c.empty())
                        throw out_of_range(__func__);

                    return C { c.begin(), c.begin() + c.size() - 1 };
                }

            };

            struct null {

                template <class C>
                auto operator()(const C & c) const {
                    return c.empty();
                }

            };

            struct length {

                template <class C>
                auto operator()(const C & c) const {
                    return c.size();
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
            };
        };
    };
};
