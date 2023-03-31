#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "graph_base.hpp"
#include "lowlink.hpp"

struct two_edge_connected_compoment {
	const UnweightedGraph &g;
	lowlink linker;
	size_t vertex;
	Vi group_id;
	UnweightedGraph tree;
	VVi groups;
	int counter;
	two_edge_connected_compoment(const UnweightedGraph &_g)
	    : g(_g),
	      linker(g),
	      vertex(_g.size()),
	      group_id(vertex, -1),
	      counter(0) {
		rep(i, g.size()) if (group_id[i] == -1)
		    two_edge_connected_compoment::dfs(i, -1);

		groups.resize(counter);
		tree.resize(counter);
		for (auto &itr : linker.bridge)
			tree[group_id[itr.first]].push_back(group_id[itr.second]);

		rep(i, vertex) groups[group_id[i]].push_back(i);
	}
	void dfs(int at, int last) {
		if (last != -1 && linker.label[last] >= linker.id[at])
			group_id[at] = group_id[last];
		else
			group_id[at] = counter++;

		for (auto &itr : linker.g[at])
			if (group_id[itr] == -1) two_edge_connected_compoment::dfs(itr, at);
	}
};
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