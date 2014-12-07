#pragma once

#include <type_traits>
#include <iterator>

#include "is_either.hpp"

namespace type_traits {
    namespace iterators {

        using std::enable_if;
        using std::iterator_traits;

        using type_traits::is_either;

        using input = std::input_iterator_tag;
        using forward = std::forward_iterator_tag;
        using bidirectional = std::bidirectional_iterator_tag;
        using random_access = std::random_access_iterator_tag;

        template <class C>
        using category = typename iterator_traits<
            typename C::iterator
        >::iterator_category;

        template <class C, class... tags>
        using enable_for = typename enable_if<
            is_either<category<C>, tags...>::value
        >::type;

    }
}
