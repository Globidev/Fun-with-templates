#pragma once

#include <utility>

#include "functional/curry.hpp"

#include "type_traits/arity.hpp"

namespace functional {
    namespace v2 {

        template <size_t ar, class Derived> struct composable {

            static constexpr size_t arity = ar;

            template <size_t inner_ar, class DerivedInner>
            auto operator^(const composable<inner_ar, DerivedInner> & inner) const {
                return composition<Derived, DerivedInner> {
                    static_cast<const Derived &>(*this),
                    static_cast<const DerivedInner &>(inner)
                };
            }

        private:

            // A composition is also composable
            // It's funny with all that CRTP inception
            template <
                class Fouter,
                class Finner,
                size_t outer_ar =  Fouter::arity,
                size_t inner_ar =  Finner::arity
            > struct composition:
                composable<outer_ar + inner_ar - 1, composition<Fouter, Finner>> {

                composition(const Fouter & outer, const Finner & inner):
                    outer_(outer), inner_(inner) { }

                template <class... Ts>
                    auto operator()(Ts &&... ts) const {
                        static_assert(
                            sizeof...(Ts) == outer_ar + inner_ar - 1,
                            "composition applied to a wrong number of arguments"
                        );

                        using std::forward;

                        return curry<outer_ar, inner_ar - 1>(
                            outer_, curry<inner_ar>(inner_)
                        )(forward<Ts>(ts)...);
                    }

            private:

                const Fouter & outer_;
                const Finner & inner_;

            };

        };

        template <size_t arity, class F>
        struct composable_impl: composable<arity, composable_impl<arity, F>> {

            composable_impl(const F & f): f_(f) { }

            template <class... Ts>
            auto operator()(Ts &&... ts) const {
                static_assert(
                    sizeof...(Ts) == arity,
                    "wrong number of arguments applied to the created composable"
                );

                using std::forward;

                return f_(forward<Ts>(ts)...);
            }

        private:

            const F & f_;

        };

        template <size_t arity, class F>
        auto make_composable(const F & f)
        {
            return composable_impl<arity, F> { f };
        }

        template <class F, size_t arity = type_traits::arity_of<F>::value>
        auto make_composable(const F & f)
        {
            return make_composable<arity>(f);
        }

    };
};
