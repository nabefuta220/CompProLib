#define PROBLEM \
	"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A"

#include "graph_base.hpp"
#include "tools.hpp"
template <typename T>
bool operator<(const edge<T>& lhs, const edge<T>& rhs) {
	return lhs.cost < rhs.cost;
}
template <typename T>
bool operator>(const edge<T>& lhs, const edge<T>& rhs) {
	return lhs.cost > rhs.cost;
}
template <typename T>
Edges<T> dijkstra(int start, WeightedGraph<T>& g) {
	T unreached = safe_max<T>();
	vector<edge<T>> dist(g.size(), edge<T>(-1, -1, unreached));
	rep(i, g.size()) dist[i].to = i;
	dist[start].cost          = 0;
	//for (auto& itr : dist) trace(itr.src, itr.to, itr.cost);
	priority_queue<edge<T>, vector<edge<T>>, greater<edge<T>>> q;
	
	q.push(dist[start]);
	edge<T> at = q.top();
	//trace(at.src, at.to, at.cost);
	while (!q.empty()) {
		at = q.top();
		
		q.pop();
		
		if (dist[at.to].cost != at.cost | dist[at.to].src != at.src) continue;
		trace("que",at.src, at.to, at.cost);
		for (auto& itr : g[at.to]) {
			if(chmin(dist[itr.to].cost,dist[at.to].cost + itr.cost)){
				dist[itr.to].src = at.to;
				q.push(dist[itr.to]);
				trace("add", dist[itr.to].src, dist[itr.to].to,
				      dist[itr.to].cost);
			}
		}
	}
	return dist;
}
int main() {
	ini(v, e, r);
	WeightedGraph<int> g = input_weightgraph<int>(v, e, true, false);
	Edges<int> dist      = dijkstra<int>(r, g);
	for (auto &d : dist) {
		if (d.cost == INF)
			cout << "INF";
		else
			cout << d.cost;

		cout << endl;
	}
}
/*

o - o - o -o
*/