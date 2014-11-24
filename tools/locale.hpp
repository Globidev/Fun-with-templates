#pragma once

#include <locale>

namespace tools {

    // Custom punctuation formatter
    struct group_numbers: std::numpunct<char>
    {
        virtual char do_thousands_sep()   const { return ' ';   }
        virtual std::string do_grouping() const { return "\03"; }
    };

    static std::locale group_numbers_locale {
        std::locale { }, new group_numbers
    };

};
