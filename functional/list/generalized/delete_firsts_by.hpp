#pragma once

#include <functional>

#include "delete_by.hpp"
#include "../fold/reduce/foldl.hpp"
#include "../../compose.hpp"

namespace functional {
    namespace list {

        static struct _delete_firsts_by: composable<3, _delete_firsts_by> {

            template <class F, class C>
            auto operator()(const F & f, const C & c1, const C & c2) const {
                using namespace std::placeholders;
                using std::bind;

                return foldl(bind(delete_by, f, _1, _2), c1, c2);
            }

        } delete_firsts_by;

    }
}
