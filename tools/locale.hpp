#pragma once

#include <locale>
// Custom punctuation formatter
struct GroupNumbers: std::numpunct<char>
{
    virtual char do_thousands_sep()   const { return ' ';   }
    virtual std::string do_grouping() const { return "\03"; }
};

static std::locale locale { std::locale(), new GroupNumbers };
