#ifndef __CONSTANCE_HPP__
#define __CONSTANCE_HPP__
#include "tools.hpp"
template <typename T>
static constexpr T safe_max() noexcept {
	return numeric_limits<T>::max() / (T)2 - (T)1;
};

constexpr long long INFLL = safe_max<long long>();
constexpr int INF         = safe_max<int>();
const double PI           = acos(-1);

#endif  // __CONSTANCE_HPP__