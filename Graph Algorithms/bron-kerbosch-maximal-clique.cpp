#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#define pb                          push_back
using namespace std;
using test=unordered_set<int>;
struct Graph : vector<int> {
	Graph(int n) : vector<int>(n) {}
};

struct AdjList : vector<tset> {
	AdjList(int n) : vector<tset>(n) {}
	void AddRelation(int u, int v){
	    at(u).insert(v);at(v).insert(u);}
};

void bronKerboschPivot(AdjList& adj, tset R, tset P,
		       tset X, vector<tset>& cliques){
    if (P.empty() && X.empty()){
        cliques.pb(R); // R is a m. clique.
        return;
    }
    // Pivot from P u X.
    int pivot;
    if (!P.empty()){
        pivot = *(P.begin());
    } else {
        pivot = *(X.begin());
    }
    tset pivotedP;
    set_difference(P.begin(), P.end(),
		   adj[pivot].begin(), adj[pivot].end(),
		   insert_iterator<tset>(pivotedP, pivotedP.begin()));
    // For all vertices in partition by pivot.
    for(int i : pivotedP){
        tset _PNi, _XNi, _R(R);
        _R.insert(i); // R u v
        set_intersection(P.begin(), P.end(),
			 adj[i].begin(), adj[i].end(),
			 insert_iterator<tset>(_PNi, _PNi.begin()));
        set_intersection(X.begin(), X.end(),
			 adj[i].begin(), adj[i].end(),
			 insert_iterator<tset>(_XNi, _XNi.begin()));
        bronKerboschPivot(adj, _R, _PNi, _XNi, cliques);
        X.insert(i);
        P.erase(i);
    }
}

