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

// Use bidirectional edges in the adjlist!!!
// Make the backflows = 0 (check for double edges in input)
int MaxFlow(vvi& flow_graph, vvi& adjacency_list,
	    int source, int sink) {
   vi parent(flow_graph.size());
   
   int maximum = 0;
   while (hasAugPath(flow_graph, adjacency_list,
		     parent, source, sink)) {
      int flow = INF;
      
      int current = sink;
      for (;current != source; current = parent[current]) {
	 int p = parent[current];
	 flow = min(flow, flow_graph[p][current]);
      }

      current = sink;
      for (; current != source; current = parent[current]) {
	 int p = parent[current];
	 flow_graph[p][current] -= flow;
	 flow_graph[current][p] += flow;
      }

      maximum += flow;
   }

   return maximum;
}
