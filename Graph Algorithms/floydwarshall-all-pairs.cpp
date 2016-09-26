#include <vector>
#include <limits>
using namespace std;

using ValueT = int;
using AdjacencyMatrix = vector< vector<ValueT> >;

const ValueT INF = numeric_limits<ValueT>::max();

struct Edge {
    int from, to;
    ValueT weight;
};

void FloydWarshall(AdjacencyMatrix& dist, const vector<Edge>& edges) {
    //post-condition: (dist.size() > 0 and dist.size() == dist[0].size());
    int size = dist.size();
    int num_edge = edges.size();

    for (int i = 0; i < size; ++i)
	for (int j = 0; j < size; ++j)
	    dist[i][j] = INF * (i != j); // 0 if i == j else INF

    for (const auto& e : edges)
	dist[e.from][e.to] = min(dist[e.from][e.to], e.weight);

    for (int k = 0; k < size; ++k) {
	for (int i = 0; i < size; ++i) {
	    for (int j = 0; j < size; ++j) {
		if (dist[i][k] == INF or dist[k][j] == INF) continue;
		dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
		/* If solving with negative cycles copy this loop and change the above line to
		   'if (dist[k][k] < 0) dist[i][j] = -INF;'*/
	    }
	}
    }
}
