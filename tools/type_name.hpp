#pragma once

#include <cxxabi.h>

namespace tools {

    template <class T>
    auto pretty_name()
    {
        return abi::__cxa_demangle(
            typeid(T).name(),
            nullptr,
            nullptr,
            nullptr
        );
    }

};
