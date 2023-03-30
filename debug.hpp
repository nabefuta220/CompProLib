#ifndef __DEBUG_HPP__

#define __DEBUG_HPP__
#include "tools.hpp"
//
template <typename U, typename = void>
struct is_specialize : false_type {};
template <typename U>
struct is_specialize<
    U, typename conditional<false, typename U::iterator, void>::type>
    : true_type {};
template <typename U>
struct is_specialize<
    U, typename conditional<false, decltype(U::first), void>::type>
    : true_type {};
template <typename U>
struct is_specialize<U, enable_if_t<is_integral<U>::value, void>> : true_type {
};
#ifdef LOCAL

void dump(const char& t) { cerr << t; }

void dump(const string& t) { cerr << t; }

void dump(const bool& t) { cerr << (t ? "true" : "false"); }

template <typename U,
          enable_if_t<!is_specialize<U>::value, nullptr_t> = nullptr>
void dump(const U& t) {
	cerr << t;
}

template <typename T>
void dump(const T& t, enable_if_t<is_integral<T>::value>* = nullptr) {
	string res;
	if (t == INF) res = "inf";
	if constexpr (is_signed<T>::value) {
		if (t == -INF) res = "-inf";
	}
	if constexpr (sizeof(T) == 8) {
		if (t == INFLL) res = "inf";
		if constexpr (is_signed<T>::value) {
			if (t == INFLL) res = "-inf";
		}
	}
	if (res.empty()) res = to_string(t);
	cerr << res;
}

template <typename T, typename U>
void dump(const pair<T, U>&);
template <typename T>
void dump(const pair<T*, int>&);

template <typename T>
void dump(const T& t,
          enable_if_t<!is_void<typename T::iterator>::value>* = nullptr) {
	cerr << "[ ";
	for (auto it = t.begin(); it != t.end();) {
		dump(*it);
		cerr << (++it == t.end() ? "" : ", ");
	}
	cerr << " ]";
}

template <typename T, typename U>
void dump(const pair<T, U>& t) {
	cerr << "( ";
	dump(t.first);
	cerr << ", ";
	dump(t.second);
	cerr << " )";
}

template <typename T>
void dump(const pair<T*, int>& t) {
	cerr << "[ ";
	for (int i = 0; i < t.second; i++) {
		dump(t.first[i]);
		cerr << (i == t.second - 1 ? "" : ", ");
	}
	cerr << " ]";
}

void trace() { cerr << endl; }
template <typename Head, typename... Tail>
void trace(Head&& head, Tail&&... tail) {
	cerr << " ";
	dump(head);
	if (sizeof...(tail) != 0) cerr << ",";
	trace(forward<Tail>(tail)...);
}
#else

void dump(const char& t) {}
void dump(const string& t) {}
void dump(const bool& t) {}

template <typename U,
          enable_if_t<!is_specialize<U>::value, nullptr_t> = nullptr>
void dump(const U& t) {}

template <typename T>
void dump(const T& t, enable_if_t<is_integral<T>::value>* = nullptr) {}

template <typename T, typename U>
void dump(const pair<T, U>&);
template <typename T>
void dump(const pair<T*, int>&);

template <typename T>
void dump(const T& t,
          enable_if_t<!is_void<typename T::iterator>::value>* = nullptr) {}

template <typename T, typename U>
void dump(const pair<T, U>& t) {}

template <typename T>
void dump(const pair<T*, int>& t) {}

void trace() { cerr << endl; }
template <typename Head, typename... Tail>
void trace(Head&& head, Tail&&... tail) {}
#endif  //__LOCAL__
#endif  // __DEBUG_HPP__