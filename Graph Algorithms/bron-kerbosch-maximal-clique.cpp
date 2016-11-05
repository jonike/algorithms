/* Bron-Kerbosch finds maximal clique in an undirected graph. */

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

using tset = unordered_set<int>;
using vtset = vector<tset>;
using vi = vector<int>;

struct Graph : vi {Graph(int n) : vi(n) {}};

struct AdjList : vtset {
	AdjList(int n) : vtset(n) {}
	void AddRelation(int u, int v){
		at(u).insert(v);
		at(v).insert(u);
	}
};

void BronKerbosch(AdjList & adj, tset R, tset P, tset X, vtset & cliques){
	if (P.empty() && X.empty()){
		cliques.pb(R);
		return;
	}

	int pivot;
	if (!P.empty()){
		pivot = *(P.begin());
	} else {
		pivot = *(X.begin());
	}

	tset pivotedP;
	set_difference(P.begin(), P.end(), adj[pivot].begin(), adj[pivot].end(), insert_iterator<tset>(pivotedP, pivotedP.begin()));
	for(int i : pivotedP){
		tset _PNi, _XNi, _R(R);
		_R.insert(i);
		set_intersection(P.begin(), P.end(), adj[i].begin(), adj[i].end(), insert_iterator<tset>(_PNi, _PNi.begin()));
		set_intersection(X.begin(), X.end(), adj[i].begin(), adj[i].end(), insert_iterator<tset>(_XNi, _XNi.begin()));
		bronKerboschPivot(adj, _R, _PNi, _XNi, cliques);
		X.insert(i);
		P.erase(i);
	}
}

int main(){
	int t;
	si(t);
	while(t--){
		vi nodes = {1, 2, 3};
		AdjList adj(3); // Contain all edges.
		adj.AddRelation(1, 2);
		adj.AddRelation(2, 3);
		vtset cliques; // The result is stored here.
		tset P(nodes.begin(), nodes.end()), R, X; // P should contain ALL nodes/vertices.
		bronKerbosch(adj, R, P, X, adj);
	}
}
