#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, rev;
    int flow, cap;
};

class Dinic {
    using AdjacencyList=vector< vector<Edge> >;

    bool bfs() {
	queue<int> q;
	q.push(source);
	fill(begin(levels), end(levels), -1);
	levels[source] = 0;
	while (!q.empty()) {
	    const auto now = q.front(); q.pop();
	    for (const auto& e : adjList[now]) {
		if (levels[e.to] == -1 && e.flow < e.cap) {
		    q.push(e.to);
		    levels[e.to] = levels[now] + 1;
		}
	    }
	}
	return levels[sink] != -1;
    }

    int dfs(int v, int flow) {
	if (flow == 0) return 0;
	if (v == sink) return flow;
	for (int & i = currentEdge[v]; i < (int) adjList[v].size(); ++i) {
	    Edge& edge = adjList[v][i];
	    if (levels[v] + 1 == levels[edge.to]) {
		const auto minimalFlow = dfs(edge.to, min(flow, edge.cap - edge.flow));
		if (minimalFlow > 0) {
		    edge.flow += minimalFlow;
		    Edge& revEdge = adjList[edge.to][edge.rev];
		    revEdge.flow -= minimalFlow;
		    return minimalFlow;
		}
	    }
	}
	return 0;
    }

    vector<int> levels, currentEdge;

public:

    int source, sink;
    AdjacencyList adjList;

    void AddEdge(int a, int b, int cap) {
	if (max(a, b) >= (int) adjList.size()) {
	    adjList.resize(max(a, b) + 1);
	    levels.resize(max(a, b) + 1);
	    currentEdge.resize(max(a, b) + 1);
	}
	const auto rev_a = adjList[b].size();
	const auto rev_b = adjList[a].size();
	adjList[a].push_back({b, rev_a, 0, cap});
	adjList[b].push_back({a, rev_b, 0, 0});
    }
    
    int MaxFlow(int s, int t) {
	source = s;
	sink = t;
	int flow = 0;
	for (;;) {
	    int m = bfs();
	    if (!m) break;
	    fill(begin(currentEdge), end(currentEdge), 0);
	    while (int pushed = dfs(source, INF)) {
		flow += pushed;
	    }
	}
	return flow;
    }
    
};
