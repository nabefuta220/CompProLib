#ifndef __TRANSIENT_HPP__
#define __TRANSIENT_HPP__

template <class T>
inline bool chmax(T& a, T b) {
	if (a < b) {
		a = b;
		return 1;
	}
	return 0;
}
template <class T>
inline bool chmin(T& a, T b) {
	if (a > b) {
		a = b;
		return 1;
	}
	return 0;
}

#endif  // __TRANSIENT_HPP__