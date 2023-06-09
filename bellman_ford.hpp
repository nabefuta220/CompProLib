#ifndef __BELLMAN_FORD_HPP__
#define __BELLMAN_FORD_HPP__
#include "graph_base.hpp"

/**
 * @brief ベルマンフォード法によって、startからの最短経路を計算する
 *
 * @param start 始点
 * @return vector<T> return[i]:startから頂点iまでの最短経路、
 * 到達不能ならばsefe_max<T>()を、 無限小ならば-sefe_max<T>()を返す
 */
template <typename T>
vector<T> bellman_ford(int start, Edges<T>& path, int vertex) {
	T unreached = safe_max<T>();
	vector<T> dist(vertex, unreached);
	dist[start] = 0;

	char updated = false;
	rep(_, vertex) {
		updated = false;
		for (auto p : path) {
			if (dist[p.src] == unreached) continue;
			updated |= chmin(dist[p.to], dist[p.src] + p.cost);
		}
		if (!updated) return dist;
	}
	for (; updated; updated = false) {
		updated = false;
		for (auto p : path) {
			if (dist[p.src] == unreached) continue;
			if (dist[p.src] == -unreached)
				dist[p.to] = -unreached, updated = true;
			if (dist[p.to] > dist[p.src] + p.cost)
				dist[p.to] = -unreached, updated = true;
		}
	}
	return dist;
}
#endif  //__BELLMAN_FORD_HPP__