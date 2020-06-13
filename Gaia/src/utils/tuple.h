#pragma once
#include <type_traits>

namespace _hidden{
	template<size_t n, size_t max, typename tuple_T, typename T>
	typename std::enable_if<n >= max>::type tuple_for_each_impl(tuple_T& tuple, T& f) {}

	template<size_t n, size_t max, typename tuple_T, typename T>
	typename std::enable_if < n < max>::type tuple_for_each_impl(tuple_T& tuple, T& f) {
		f(std::get<n>(tuple));
		return tuple_for_each_impl<n + 1, max>(tuple, f);
	}
}

template<typename tuple_T, typename T>
void tuple_for_each(tuple_T& tuple, T& f) {
	_hidden::tuple_for_each_impl<0, std::tuple_size<std::decay_t<tuple_T>>::value>(tuple, f);
}