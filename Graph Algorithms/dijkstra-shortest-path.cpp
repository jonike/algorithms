#include <limits>
#include <vector>
#include <queue>
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

using AdjacencyList = vector< vector<Edge> >;

void Dijkstra(vector<Node>& nodes, AdjacencyList& adjList, int start) {
    struct State {
	ValueT dist;
	int node;
	bool operator() (const State& lhs, const State& rhs) {
	    return lhs.dist > rhs.dist;
	}
    };

    // Use comparator in state
    priority_queue<State, vector<State>, State> pq;
    pq.push({0, start});
    nodes[start].dist = 0;

    vector<bool> visited(nodes.size());
    while(!pq.empty()) {
	const auto state = pq.top(); pq.pop();
	const auto node = state.node;
	if (visited[node]) continue;

	visited[node] = true;
	for (const auto& e : adjList[node]) {
	    ValueT next_dist = nodes[e.from].dist + e.weight;
	    if (next_dist < nodes[e.to].dist) {
		nodes[e.to].dist = next_dist;
		pq.push({next_dist, e.to});
	    }
	}
    }
}
