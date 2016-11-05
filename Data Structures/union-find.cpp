/* Disjoint-set data structure ("Union-find"). */
#include <vector>
using namespace std;

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
