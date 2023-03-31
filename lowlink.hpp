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
			if (label[i] == -1) count = lowlink::dfs(i, -1, count);
	}

	int dfs(int at, int last, int count) {
		bool articulat = false, first_last = false;
		int visit_count = 0;
		// label
		label[at] = count++;
		id[at]    = label
		    [at];  // id.labelは通常はidのほうが小さくなる、子はlabalが大きくなるはず
		// 深さ優先探索
		for (auto &itr : g[at]) {
			if (itr == last && !first_last) {  // 親に初めて訪れる(二重辺防止)
				first_last = true;

			} else if (label[itr] == -1) {  // 初めて訪れる場合
				// trace(at, "->", itr);

				count = dfs(itr, at, count);
				++visit_count;  // 訪問順の調整
				chmin(id[at],
				      id[itr]);  // apply id(子が逆辺を通ってたどりつける辺)
				// det 関節点の検出(始点以外)
				articulat |= (last != -1) && (id[itr] >= label[at]);

				// det 橋の検出
				if (label[at] < id[itr]) {
					// add brige
					trace(at, itr);
					bridge.emplace_back(at, itr);
				}

			} else {  // 逆辺をたどって到達できる(1回のみ)
				chmin(id[at], label[itr]);
			}
		}
		// def 関節点の検出(始点)
		articulat |= (last == -1) && (visit_count > 1);
		if (articulat) articulation.push_back(at);
		// add articlat

		return count;
	}
};
#endif  // __LOWLINK_HPP__