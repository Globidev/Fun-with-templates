#pragma once

#include <memory>
#include <algorithm>

#include "../compose.hpp"

namespace functional {
    namespace maybe {

        template <class T> struct maybe_t {

            using Type = T;

            // Construction
            maybe_t() {}
            maybe_t(const T & t): value(new T(t)) {}
            maybe_t(const maybe_t<T> & other) {
                if (other.value)
                    value.reset(new T(*other.value));
                else
                    value.reset(nullptr);
            }
            maybe_t(maybe_t<T> && other): value(std::move(other.value)) {}

            // Assignment
            maybe_t<T> & operator=(const T & t) {
                value.reset(new T(t));
                return *this;
            }
            maybe_t<T> & operator=(const maybe_t<T> & other) {
                if (other.value)
                    value.reset(new T(*other.value));
                else
                    value.reset(nullptr);
                return *this;
            }
            maybe_t<T> & operator=(maybe_t<T> && other) {
                value = std::move(other.value);
                return *this;
            }

            // Access
            template <class R, class Fjust>
            R visit(const Fjust & f_just, const R & default_val) const {
                return value ? f_just(*value) : default_val;
            }

        private:

            std::unique_ptr<T> value;

        };

        // Comparison
        template <class T>
        inline bool operator==(const maybe_t<T> & lhs, const maybe_t<T> & rhs)
        {
            auto just_f = [](const T &) { return true; };
            auto id = [](const T & t) { return t; };
            if (lhs.visit(just_f, false) == rhs.visit(just_f, false))
                return lhs.visit(id, T{}) == rhs.visit(id, T{});
            return false;
        }

        // Conveniency constructors
        static struct _just: composable<1, _just> {

            template <class T>
            auto operator()(const T & t) const {
                return maybe_t<T> { t };
            }

        } just;

        template <class T> maybe_t<T> nothing = { };

    }
}
