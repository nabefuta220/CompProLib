#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "graph_base.hpp"
#include "lowlink.hpp"
void dfs(int at, int last, Vi &group, lowlink &lowlinker, int &counter) {
	if (last != -1 && lowlinker.label[last] >= lowlinker.id[at]) {
		group[at] = group[last];
	} else {
		group[at] = counter++;
	}
	for (auto &itr : lowlinker.g[at]) {
		if (group[itr] == -1) {
			dfs(itr, at, group, lowlinker, counter);
		}
	}
}
int main() {
	ini(n, m);
	UnweightedGraph g = input_unwightgraph(n, m, false, false);
	lowlink linker(g);

	Vi group(n, -1);
	int counter = 0;
	rep(i, n) {
		if (group[i] == -1) {
			dfs(i, -1, group, linker, counter);
		}
	}
	VVi ans(counter);
	rep(i, n) { ans[group[i]].push_back(i); }
	output(ans.size());
	for (auto &itr : ans) {
		output(itr.size(), itr);
	}
}