/* A Fenwick tree (binary indexed tree) data structure. */
#include <vector>
using namespace std;

using ll = long long;

class fenwick_tree{
private:
    vector<ll> tree;
public:
    fenwick_tree(ll n){reset(n);}
    void reset(ll n){tree.assign(n + 1, 0);}

    // Calculates sum of values at indices [1, 2, ... i].
    ll sum(ll idx){
        ll sum = 0;
        while(idx > 0){
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }

    // Adds a value x to index i.
    void add(ll idx, ll x){
        while(idx < tree.size()){
            tree[idx] += x;
            idx += idx & (-idx);
        }
    }
};
