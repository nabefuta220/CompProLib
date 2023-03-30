#ifndef __WARSHALL_FLOYD_HPP__
#define __WARSHALL_FLOYD_HPP__
#include "tools.hpp"
template <typename T>
vector<vector<T>> warshall_floyd(vector<vector<T>>& g) {
	size_t size = g.size();
	T unreached = safe_max<T>();
	rep(u, size) rep(s, size) rep(t, size) g[s][u] != unreached&& g[u][t] !=
	    unreached&& chmin(g[s][t], g[s][u] + g[u][t]);
	return g;
}
#endif  //__WARSHALL_FLOYD_HPP__d