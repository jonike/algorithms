#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <climits>
#define DEBUG
// Bitstuff.
#define checkbit(x,n)                ( (x >> n) & 1) // Checks if bit n in number x is set.
// Input / Output.
#define si(n)                       scanf("%d",&n)
#define sc(n)                       scanf("%c",&n)
#define sl(n)                       scanf("%lld",&n)
#define sf(n)                       scanf("%lf",&n)
#define ss(n)                       scanf("%s",n)
#define pi(n)                       printf("%d",n)
#define pc(n)                       printf("%c",n)
#define pl(n)                       printf("%lld",n)
#define pd(n)                       printf("%lf", n)
#define ps(n)                       printf("%s", n.c_str())
// Useful constants
#define INF                         (int)1e9
#define EPS                         1e-9
// Useful container manipulation / traversal macros
#define in(a,b)                     ((b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                    memset(a, v, sizeof(a))
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair
#define FOR(k,a,b) for(typeof(a) k=(a); k <= (b); ++k)
#define REP(k,a) for(int k=0; k < (a); ++k)
// Math.
#define maxi(a,b)                     ( (a) > (b) ? (a) : (b))
#define mini(a,b)                     ( (a) < (b) ? (a) : (b))
// Using.
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> ivec;
typedef vector<string> svec;
typedef pair<int, int> pint;
typedef map<int, int> tmap;
typedef unordered_set<int> tset;
template<typename T1, typename T2, typename T3>
struct triple {T1 first;T2 second;T3 third;triple(T1 f, T2 s, T3 t) : first(f), second(s), third(t){}};
// Math.
inline int cint(char c){return c - '0';}
inline char intc(int i){return '0' + i;}
int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}
inline bool EQ(double a, double b) { return fabs(a-b) < EPS; }
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
struct Graph : vector<int> {
	Graph(int n) : vector<int>(n) {}
};

struct AdjList : vector<tset> {
	AdjList(int n) : vector<tset>(n) {}
	void AddRelation(int u, int v){at(u).insert(v);at(v).insert(u);}
};

void bronKerboschPivot(AdjList& adj, tset R, tset P, tset X, vector<tset>& cliques){
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
    set_difference(P.begin(), P.end(), adj[pivot].begin(), adj[pivot].end(), insert_iterator<tset>(pivotedP, pivotedP.begin()));
    // For all vertices in partition by pivot.
    for(int i : pivotedP){
        tset _PNi, _XNi, _R(R);
        _R.insert(i); // R u v
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
        ivec nodes = {1, 2, 3};
        AdjList adj(3); // Contain all edges.
        adj.AddRelation(1, 2);
        adj.AddRelation(2, 3);
        vector<tset> cliques; // The result is stored here.
        tset P(nodes.begin(), nodes.end()), R, X; // P should contain ALL nodes/vertices.
        bronKerboschPivot(adj, R, P, X, adj);
    }
}
