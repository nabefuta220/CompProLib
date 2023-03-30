#define PROBLEM \
	"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A"

#include "dijkstra.hpp"
#include "graph_base.hpp"
#include "tools.hpp"
int main() {
	ini(v, e, r);
	WeightedGraph<int> g = input_weightgraph<int>(v, e, true, false);
	Edges<int> dist      = dijkstra<int>(r, g);
	for (auto& d : dist) {
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