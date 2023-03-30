#define PROBLEM \
	"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B"

#include "graph_base.hpp"
#include "tools.hpp"

int main() {
	ini(v, e, r);
	Edges<int> path = input_edgegraph<int>(e, true, false);

	// bellman ford
	vector<int> dist(v, INF);
	dist[r] = 0;
	rep(_, v) for (auto p : path) {
		if (dist[p.src] == INF) continue;
		chmin(dist[p.to], dist[p.src] + p.cost);
	}

	// cout << dist << endl;
	for (auto p : path) {
		if (dist[p.src] == INF) continue;
		if (dist[p.to] > dist[p.src] + p.cost) dist[p.to] = -INF;
	}
	// end of bellman ford
	int detected = false;
	for (auto d : dist) detected |= (d == -INF);

	if (detected)
		cout << "NEGATIVE CYCLE" << endl;
	else
		rep(i, v) {
			if (dist[i] == INF)
				cout << "INF";
			else
				cout << dist[i];

			cout << endl;
		}
}
/*

o - o - o -o
*/