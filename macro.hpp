#ifndef __MACRO_HPP__
#define __MACRO_HPP__
#include "tools.hpp"
using ll = long long;
#define rep(i, n) for (int i = 0, i##_len = (int)(n); i < i##_len; ++i)
#define reps(i, n) for (int i = 1, i##_len = (int)(n); i <= i##_len; ++i)
#define rrep(i, n) for (int i = ((int)(n)-1); i >= 0; --i)
#define rreps(i, n) for (int i = ((int)(n)); i > 0; --i)
#define repi(i, x) \
	for (auto i = (x).begin(), i##_fin = (x).end(); i != i##_fin; ++i)
#define all(x) (x).begin(), (x).end()
#define F first
#define S second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
using Vi  = vector<int>;
using VVi = vector<Vi>;
using Pi  = pair<int, int>;
using VPi = vector<Pi>;
using V   = vector<long long>;
using VV  = vector<V>;
using P   = pair<long long, long long>;
using VP  = vector<P>;
using Vb  = vector<bool>;

// decler and input
#define ini(...)     \
	int __VA_ARGS__; \
	input(__VA_ARGS__);
#define inl(...)           \
	long long __VA_ARGS__; \
	input(__VA_ARGS__);
#define ind(...)        \
	double __VA_ARGS__; \
	input(__VA_ARGS__);
#define ins(...)        \
	string __VA_ARGS__; \
	input(__VA_ARGS__);
#define inv2(s, t) rep(i, (s).size()) input(s[i], t[i]);
#define inv3(s, t, u) rep(i, (s).size()) input(s[i], t[i], u[i]);
#define inv4(s, t, u, v) rep(i, (s).size()) input(s[i], t[i], u[i], v[i]);
#endif  //__MACRO_HPP__