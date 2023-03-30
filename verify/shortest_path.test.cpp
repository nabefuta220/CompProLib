#include <bits/stdc++.h>

#include "tools.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "dijkstra.hpp"
int main() {
	ini(n, m, s, t);
	WeightedGraph<long long> g = input_weightgraph<ll>(n, m, true, false);
	Edges<ll> dist             = dijkstra(s, g);
	Edges<ll> ans;
	ans.push_back(dist[t]);
	if (ans.front().cost == INFLL) {
		cout << -1 << endl;
		return 0;
	}
	while (ans.back().src != s) {
		ans.push_back(dist[ans.back().src]);
	}
	reverse(all(ans));
	output(dist[t].cost, ans.size());
	for (auto& path : ans) {
		output(path.src, path.to);
	}
}