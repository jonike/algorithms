#include <vector>
using namespace std;

using AdjacencyList = vector< vector<int> >;

vector<int> Toposort(AdjacencyList& adjList) {
    struct Node {
	int idx{}, cnt{};
    };
    
    vector<Node> nodes(adjList.size());
    for (int i = 0; i < (int) adjList.size(); ++i) {
	nodes[i].idx = i;
	for (int k : adjList[i]) {
	    nodes[k].cnt++;
	}
    }

    vector<int> ret;
    for (const auto& n : nodes) {
	if (n.cnt == 0) {
	    ret.push_back(n.idx);
	}
    }

    for (int i = 0; i < (int) ret.size(); ++i) {
	int now = ret[i];
	for (const auto k : adjList[now]) {
	    Node& other = nodes[k];
	    other.cnt--;
	    if (other.cnt == 0) ret.push_back(other.idx);
	}
    }
    
    return ret;
}
