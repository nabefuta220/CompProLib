#define IGNORE 1
// atcoder問題
#define PROBLEM "https://atcoder.jp/contests/abc061/tasks/abc061_d"
// verifyed : https://atcoder.jp/contests/abc061/submissions/40161018
#include "bellman_ford.hpp"
#include "tools.hpp"

int main() {
	ini(n, m);
	Edges<long long> path = input_edgegraph<long long>(m, true, true);
	for (auto& itr : path) itr.cost *= -1;
	V dist = bellman_ford<>(0, path, n);
	if (dist[n - 1] == -INFLL) {
		cout << "inf";
	} else {
		cout << -dist[n - 1];
	}
	cout << endl;
}