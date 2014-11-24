#pragma once

#include <utility>
#include <type_traits>

namespace type_traits {

    using std::enable_if;
    using std::integer_sequence;

    // builds an integer sequence of <start, start + 1, ..., end - 1>
    template <size_t start, size_t end, class enabler = void, size_t... seq>
    struct make_range_index_sequence:
        make_range_index_sequence<start + 1, end, void, seq..., start> { };

    template <size_t start, size_t end, size_t... seq>
    struct make_range_index_sequence<
        start,
        end,
        typename enable_if<start == end>::type,
        seq...
    >: integer_sequence<size_t, seq...> { };

};
