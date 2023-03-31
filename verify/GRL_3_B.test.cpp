#define PROBLEM \
	"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"
#include "graph_base.hpp"
#include "lowlink.hpp"
int main() {
	ini(v, e);
	UnweightedGraph g = input_unwightgraph(v, e, false, false);
	lowlink linker(g);
	VPi brige = linker.bridge;

	for (auto &edge : brige)
		if (edge.first > edge.second) swap(edge.first, edge.second);
	sort(all(brige));

	for (auto &itr : brige) {
		cout << itr.first << ' ' << itr.second << '\n';
	}
}