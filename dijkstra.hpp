#ifndef __DIJKSTRA_HPP__
#define __DIJKSTRA_HPP__
#include "graph_base.hpp"
/**
 * @brief startからの最短経路を求める
 *
 * @param start 始点
 * @return Edges<T> src:前の頂点,cost:
 * start->toまでの距離、到達不能ならばsafe_max<T>
 */
template <typename T>
Edges<T> dijkstra(int start, WeightedGraph<T>& g) {
	T unreached = safe_max<T>();
	vector<edge<T>> dist(g.size(), edge<T>(-1, -1, unreached));
	rep(i, g.size()) dist[i].to = i;
	dist[start].cost            = 0;
	priority_queue<edge<T>, vector<edge<T>>, greater<edge<T>>> q;
	q.push(dist[start]);
	edge<T> at = q.top();

	while (!q.empty()) {
		at = q.top();
		q.pop();
		if (dist[at.to].cost != at.cost || dist[at.to].src != at.src) continue;

		for (auto& itr : g[at.to])
			if (chmin(dist[itr.to].cost, dist[at.to].cost + itr.cost)) {
				dist[itr.to].src = at.to;
				q.push(dist[itr.to]);
			}
	}
	return dist;
}
#endif  //__DIJKSTRA_HPP__