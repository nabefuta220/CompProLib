#ifndef __GRAPH_BASE_HPP__
#define __GRAPH_BASE_HPP__
#include "tools.hpp"
// 辺の情報
template <typename T>
struct edge {
	int src, to;
	T cost;
	// 重みなし辺の追加
	edge(int _to, T _cost) : src(-1), to(_to), cost(_cost) {}
	// 重み付き辺の追加
	edge(int _src, int _to, T _cost) : src(_src), to(_to), cost(_cost) {}
};
//edgeに関する演算子
template <typename T>
bool operator<(const edge<T>& lhs, const edge<T>& rhs) {
	return lhs.cost < rhs.cost;
}
template <typename T>
bool operator>(const edge<T>& lhs, const edge<T>& rhs) {
	return lhs.cost > rhs.cost;
}
// 辺の集合
template <typename T>
using Edges = vector<edge<T>>;

// 重み付きグラフ
template <typename T>
using WeightedGraph = vector<Edges<T>>;
// 重みなしグラフ
using UnweightedGraph = vector<vector<int>>;
// 隣接行列
template <typename T>
vector<vector<T>> input_adjmtrgraph(int v, int e, T undef_value,
                                    bool weighted = true, bool directed = true,
                                    bool indexed_1 = true) {
	vector<vector<T>> d(v, vector<T>(v, undef_value));
	for (int i = 0; i < e; ++i) {
		int s, t;
		T c;
		cin >> s >> t;
		if (indexed_1) --s, --t;
		if (weighted)
			cin >> c;
		else
			c = 1;
		d[s][t] = c;
		if (!directed) d[t][s] = c;
	}
	return d;
}

// 重みなしグラフの入力
UnweightedGraph input_unwightgraph(int v, int e = -1, bool directed = true,
                                   bool indexed_1 = true) {
	UnweightedGraph g(v);
	if (e == -1) e = v - 1;
	for (int i = 0; i < e; ++i) {
		int s, t;
		cin >> s >> t;
		if (indexed_1) s--, t--;
		g[s].push_back(t);
		if (!directed) g[t].push_back(s);
	}
	return g;
}

// 重みありグラフの入力
template <typename T>
WeightedGraph<T> input_weightgraph(int v, int e = -1, bool directed = true,
                                  bool indexed_1 = true) {
	WeightedGraph<T> g(v);
	if (e == -1) e = v - 1;
	for (int i = 0; i < e; ++i) {
		int s, t;
		cin >> s >> t;
		T c;
		cin >> c;
		if (indexed_1) s--, t--;
		g[s].emplace_back(s, t, c);
		if (!directed) g[t].emplace_back(t, s, c);
	}
	return g;
}

// Input of Edges
template <typename T>
Edges<T> input_edgegraph(int e, int weighted = true, bool indexed_1 = true) {
	Edges<T> es;
	for (int i = 0; i < e; ++i) {
		int s, t;
		cin >> s >> t;
		T c;
		if (weighted)
			cin >> c;
		else
			c = 1;
		if (indexed_1) s--, t--;
		es.emplace_back(s, t, c);
	}
	return es;
}
#endif  //__GRAPH_BASE_HPP__