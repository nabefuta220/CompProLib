#define PROBLEM \
	"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A"
#include "graph_base.hpp"
int dfs(int at, int last, UnweightedGraph &g, Vi &label, Vi &id, VPi &brige,
        Vi &articulation, int count) {
	bool articulat = false, first_last = false;
	int visit_count = 0;
	// label
	label[at] = count++;
	id[at]    = label[at];
	trace(at, count - 1);
	for (auto &itr : g[at]) {
		if (itr == last && !first_last) {
			first_last = true;

		} else if (label[itr] == -1) {  // visit
			trace(at, "->", itr);

			count = dfs(itr, at, g, label, id, brige, articulation, count);
			++visit_count;
			chmin(id[at], id[itr]);  // apply id
			// det articulat point
			articulat |= (last != -1) && (id[itr] >= label[at]);

			// det brige
			if (label[at] < id[itr]) {
				// add brige
				trace(at, itr);
				brige.emplace_back(at, itr);
			}
			trace(at, "id", id[at]);

		} else {
			chmin(id[at], label[itr]);
			trace(at, "id", id[at]);
		}
	}
	// def for parament
	articulat |= (last == -1) && (visit_count > 1);
	if (articulat) {
		articulation.push_back(at);
		// add articlat
	}

	return count;
}
int main() {
	ini(v, e);
	UnweightedGraph g = input_unwightgraph(v, e, false, false);
	Vi label(v, -1);
	Vi id(v, -1);
	int count = 0;
	VPi brige;
	Vi arti;
	rep(i, v) {
		if (label[i] == -1)
			count = dfs(i, -1, g, label, id, brige, arti, count);
	}
	sort(all(arti));
	for (int ans : arti) output(ans);
}