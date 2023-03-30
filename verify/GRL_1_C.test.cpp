#define PROBLEM \
	"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"

#include "graph_base.hpp"
#include "tools.hpp"
template <typename T>
vector<vector<T>> warshall_floyd(vector<vector<T>>& g) {
	size_t size = g.size();
	rep(s, size) rep(t, size) rep(u, size) chmin(g[s][t], g[s][u] + g[u][t]);
	return g;
}
int main() {
	ini(v, e);
	vector<vector<ll>> g = input_adjmtrgraph(v, e, INFLL, true, true, false);
	rep(i, v) g[i][i]    = 0LL;
	g                    = warshall_floyd(g);
	rep(i, v) {
		if (g[i][i] != 0) {
			cout << "NEGATIVE CYCLE\n";
			return 0;
		}
	}
	for (auto& itr : g) {
		rep(i, v) {
			if (itr[i] == INFLL)
				cout << "INF";
			else
				cout << itr[i];
			if (i != v - 1)
				cout << " ";
			else
				cout << endl;
		}
	}
}
/*

o - o - o -o
*/