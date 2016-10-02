#include <limits>
#include <vector>
using namespace std;

using ValueT = int;
const ValueT INF = numeric_limits<ValueT>::max();

struct Node {
    ValueT dist{INF};
};

struct Edge {
    int from, to;
    ValueT weight;
};

void BellmanFord(vector<Node>& nodes, vector<Edge>& edgeList,
		 int start, int num_nodes, int num_edges) {
    nodes[start].dist = 0; 
    for (int i = 1; i < num_nodes; ++i) {
	for (auto& e : edgeList) {
	    if (nodes[e.from].dist != INF) {
		relaxed = nodes[e.from].dist + e.weight;
		nodes[e.to].dist = min(nodes[e.to].dist, 
				       relaxed);
	    }
	}
    }
		
    for (int i = 1; i < num_nodes; ++i) {
	for (auto& e : edgeList) {
	    if (nodes[e.from].dist == INF) continue;
		
	    ValueT dist = nodes[e.from].dist + e.weight;
	    ValueT other = nodes[e.to].dist;
		
	    if (dist < other)
		nodes[e.to].dist = -INF;
	}
    }
}
