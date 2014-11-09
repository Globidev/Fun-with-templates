#pragma once

#include <functional>

namespace functional {

	using std::result_of;
	using std::enable_if;
	using std::forward;

	// Composition internal
	template <
		int n,
		class Ft,
		class... Empty,
		class... T,
		class enabler = typename enable_if<n == 1, void>::type
	>
	auto compose_impl(T &&... t) -> typename result_of<Ft(T...)>::type
	{
		Ft ft;

		return ft(forward<T>(t)...);
	}

	template <
		int n,
		class Fh,
		class... Fs,
		class... T,
		class enabler = typename enable_if<n >= 2, void>::type
	>
	auto compose_impl(T &&... t)
	{
		Fh fh;

		return fh(compose_impl<n - 1, Fs...>(forward<T>(t)...));
	}

	struct must_pass_at_least_two_functors; // client helper

	// Main function
	template <
		class... Fn,
		class... T,
		// Validity check (Need at least two functions to compose)
		int n = sizeof...(Fn),
		class enabler = typename enable_if<
			n >= 2, must_pass_at_least_two_functors
		>::type
	>
	auto compose(T &&... t)
	{
		return compose_impl<n, Fn...>(forward<T>(t)...);
	}

};
