/* Kruskal's algorithm for minimum spanning trees. */
#include <vector>
#include <algorithm>
using namespace std;

using weight_type = long long;
using edge = pair<weight_type, pair<int, int>>; // w, x, y

class union_set{
private:
    vector<int> parent;
public:
    union_set(int size){reset(size);}

    inline void unify(int a, int b){
        a = find(a);
        parent[a] = find(b);
    }

    inline void reset(int n){
        parent.resize(n);
        for(int i = 0; i < n; ++i){parent[i] = i;}
    }

    inline int find(int x){
        int& y = parent[x];
        if(x != y){y = find(y);}
        return y;
    }
};

// Undirected edges. Returns the MST.
vector<edge> kruskal_mst(vector<edge>& edges, const int number_of_nodes){
    vector<edge> mst_out;
    sort(edges.begin(), edges.end());
    union_set us(number_of_nodes);
    for(const auto& e : edges){
        if(mst_out.size() >= number_of_nodes - 1){break;}
        const auto& c = e.second;
        if(us.find(c.first) != us.find(c.second)){
            mst_out.push_back(e);
            us.unify(c.first, c.second);
        }
    }
    return mst_out;
}
