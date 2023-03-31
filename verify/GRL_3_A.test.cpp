#define PROBLEM \
	"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A"
#include "graph_base.hpp"
#include "lowlink.hpp"
int main() {
	ini(v, e);
	UnweightedGraph g = input_unwightgraph(v, e, false, false);

	lowlink linker(g);
	Vi arti = linker.articulation;

	sort(all(arti));
	for (int ans : arti) output(ans);
}