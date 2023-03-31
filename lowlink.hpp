#ifndef __LOWLINK_HPP__
#define __LOWLINK_HPP__
#include "graph_base.hpp"
/**
 * @brief 関節点・橋を求めるアルゴリズム
 * 
 */
struct lowlink {
	const UnweightedGraph &g;
	int vertex;
	vector<int> label, id, articulation;
	vector<pair<int, int> > bridge;

	lowlink(const UnweightedGraph &_g)
	    : g(_g), vertex(g.size()), label(vertex, -1), id(vertex, -1) {
		for (int i = 0, count = 0; i < vertex; i++)
			if (label[i] == -1) count = dfs(i, -1, count);
	}

	int dfs(int at, int last, int count) {
		bool articulat = false, first_last = false;
		int visit_count = 0;
		// label
		label[at] = count++;
		id[at]    = label[at];

		for (auto &itr : g[at]) {
			if (itr == last && !first_last) {
				first_last = true;

			} else if (label[itr] == -1) {  // visit
				// trace(at, "->", itr);

				count = dfs(itr, at, count);
				++visit_count;
				chmin(id[at], id[itr]);  // apply id
				// det articulat point
				articulat |= (last != -1) && (id[itr] >= label[at]);

				// det brige
				if (label[at] < id[itr]) {
					// add brige
					trace(at, itr);
					bridge.emplace_back(at, itr);
				}

			} else {
				chmin(id[at], label[itr]);
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
};
#endif  // __LOWLINK_HPP__