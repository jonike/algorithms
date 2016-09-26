#include <vector>
#include <limits>
#include <queue>
using namespace std;

using ValueT = long long;
using vi=vector< int >;
using vvi=vector< vi >;

const int INF = numeric_limits<ValueT>::max();

bool hasAugPath(vvi& flow_graph, vvi& adj, vi& parent,
		int s, int t) {
    vector<bool> visited(flow_graph.size());
    queue<int> q;
    q.push(s);
    parent[s] = -1;
    visited[s] = true;

    while (!q.empty()) {
	int now = q.front(); q.pop();

	for (int n : adj[now]) {
	    if (not visited[n] and flow_graph[now][n] > 0) {
		parent[n] = now;
		visited[n] = true;
		q.push(n);
		if (n == t) {
		    return true;
		}
	    }
	}
    }

    return false;
}

/** It is important to create the adjecency list with bidirectional edges! */
// Flow graph == Residual graph with capacities applied (only one direction)
int MaxFlow(vvi& flow_graph, vvi& adjacency_list, int source, int sink) {
   vi parent(flow_graph.size());
   
   int maximum = 0;
   while (hasAugPath(flow_graph, adjacency_list, parent, source, sink)) {
      int flow = INF;
      
      // Search through path for limiting flow
      for (int current = sink; current != source; current = parent[current]) {
	 int p = parent[current];
	 flow = min(flow, flow_graph[p][current]);
      }

      // Fill path with limiting flow
      for (int current = sink; current != source; current = parent[current]) {
	 int p = parent[current];
	 flow_graph[p][current] -= flow;
	 flow_graph[current][p] += flow;
      }

      maximum += flow;
   }

   return maximum;
}
