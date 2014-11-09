#pragma once

namespace functional {
    namespace list {

        struct minimum {

            template <class C>
            auto operator()(const C & c) const {
                using std::out_of_range;
                using std::min_element;

                if (c.empty())
                    throw out_of_range(__func__);

                return *min_element(c.begin(), c.end());
            }

        };

        namespace impl {

            struct minimum minimum;

        };
    };
};