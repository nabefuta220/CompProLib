#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "graph_base.hpp"
#include "two_edge_connected_compoment.hpp"

int main() {
	ini(n, m);
	UnweightedGraph g = input_unwightgraph(n, m, false, false);
	two_edge_connected_compoment comper(g);

	VVi ans = comper.groups;

	output(ans.size());
	for (auto &itr : ans) {
		output(itr.size(), itr);
	}
}