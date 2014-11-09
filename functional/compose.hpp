#pragma once

#include <functional>

#include "tools/parameter_pack.hpp"

namespace functional {

	// Composition internal
	template <
		int N,
		template <class...> class Ft,
		template <class...> class ... Empty,
		class T,
		//
		class DecayedT = typename std::decay<T>::type,
		class CFt = Ft<DecayedT>,
		class R = typename std::result_of<CFt(DecayedT)>::type
	>
	typename std::enable_if<N == 1, R>::type compose_impl(T && t)
	{
		CFt ft;

		return ft(std::forward<T>(t));
	}

	template <
		int n,
		template <class...> class Fh,
		template <class...> class ... Fs,
		class T,
		//
		class check = typename std::enable_if<n >= 2, void>::type,
		//
		class CFh = Fh<typename RFoldResultOf<n - 1, T, Fs...>::R>,
		class R = typename std::result_of<CFh(T)>::type
	>
	R compose_impl(T && t)
	{
		CFh fh;

		return fh(compose_impl<n - 1, Fs...>(
			std::forward<T>(t)
		));
	}

	struct must_pass_at_least_two_functors; // client helper
	// Main function
	template <
		// Explicit functors templates
		template <class...> class Fh,
		template <class...> class ... Fs,
		// Deduced arguments type
		class ... T,
		// Validity check (Need at least two functions to compose)
		int n = sizeof...(Fs) + 1,
		class check = typename std::enable_if<
			n >= 2, must_pass_at_least_two_functors
		>::type,
		// Concrete tail functor
		class CFt = typename Last<Fs...>::template type<
			typename std::decay<T>::type...
		>,
		// Tail functor return type
		class Rt = typename std::result_of<CFt(
			typename std::decay<T>::type...
		)>::type,
		// Composition return type
		class R = typename RFoldResultOf<n - 1, Rt, Fh, Fs...>::R
	>
	R compose(T && ... t)
	{
		CFt ft;

		return compose_impl<n - 1, Fh, Fs...>(
			ft(std::forward<T>(t)...)
		);
	}

};
