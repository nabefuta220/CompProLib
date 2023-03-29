#ifndef __IO_HPP__
#define __IO_HPP__
// 入出力関連
#include "macro.hpp"
#include "tools.hpp"
// pair
template <class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
	os << "(" << p.first << " " << p.second << ")";
	return os;
}

template <class T, class U>
istream& operator>>(istream& is, pair<T, U>& p) {
	is >> p.first >> p.second;
	return is;
}
// vector
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	rep(i, v.size()) {
		if (i) os << " ";
		os << v[i];
	}
	return os;
}
template <class T>
istream& operator>>(istream& is, vector<T>& v) {
	rep(i, v.size()) { is >> v[i]; }
	return is;
}

// multi-variable
void input() {}
template <typename T, class... U>
void input(T& t, U&... u) {
	cin >> t;
	input(u...);
}

void output() { cout << '\n'; }
template <typename T, class... U, char seperate = ' '>
void output(const T& t, const U&... u) {
	cout << t;
	if (sizeof...(u)) cout << seperate;
	out(u...);
}

// setup
struct IoSetuper {
	IoSetuper() {
		cin.tie(nullptr);
		ios::sync_with_stdio(false);
		cout << fixed << setprecision(15);
		cerr << fixed << setprecision(7);
	}
} iosetuper;
#endif  //__IO_HPP__