#pragma once
#include <ostream>     // ostream
#include <type_traits> // enable_if, is_enum, underlying_type

enum class State : char { invalid='-', empty='0', full='1' };

// http://stackoverflow.com/a/28206799/514165
template <typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& out, const T& e) {
	return out << static_cast<typename std::underlying_type<T>::type>(e);
}
