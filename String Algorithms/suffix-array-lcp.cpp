#include <iostream>
#include <vector>
#include <algorithm>
#define pb        push_back
#define mp        make_pair
#define REP(k,a)  for(auto k=decltype(a)(0); k < (a); ++k)
using namespace std;
struct Suffix {
    int index;
    int rank[2];
    bool operator<(const Suffix& b) const {
        if(rank[0] != b.rank[0]){return rank[0] < b.rank[0];}
        return rank[1] < b.rank[1];
    }
};
// Constructs the suffix array when constructor is called.
// Generates the LCP by calling GenerateLCP member function.
vector<vector<int>> __rmem; // reuse
struct SuffixArray{
private:
    vector<Suffix> suffixes;
    vector<int> lcp;
    const string& s;
public:
    const int n; // size of suffix array 
    inline vector<Suffix>& get_array() {return suffixes;}
    inline vector<int>& get_LCP() {return lcp;}
    inline int index(int i) {return suffixes[i].index;}
    inline Suffix& suffix(int i) {return suffixes[i];}
    inline int size() {return n;}
    // Generates the LCP for a given string using Kasai's
    // algorithm. Returns the lcp vector.
    vector<int>& gen_LCP(){
        vector<int> inv(n, 0);
        lcp.assign(n, 0);
        REP(i, n){
            inv[suffixes[i].index] = i;
        }
        int prev_len = 0;
        REP(i, n){
            if(inv[i] == n - 1){
                prev_len = 0;
                continue;
            }
            int j = suffixes[inv[i] + 1].index;
            while(i + prev_len < n and j + prev_len < n and
		  s[i + prev_len] == s[j + prev_len]){
                ++prev_len;
            }
            lcp[inv[i]] = prev_len;
            if(prev_len > 0){
                --prev_len; // Remove start.
            }
        }
        return lcp;
    }
    SuffixArray(const string& _s) : s(_s), n(_s.length()){
        __rmem.assign(20, vector<int>(n));
        suffixes.resize(n);
        int iteration, count;
        REP(i, n){__rmem[0][i] = (int) s[i];}
        for(iteration = count = 1; count < n * 2;
	    ++iteration, count *= 2){
            REP (i, n){
                suffixes[i].rank[0] = __rmem[iteration - 1][i];
                if(i + count < n){
                    suffixes[i].rank[1] =
			__rmem[iteration - 1][i + count];
                } else {
                    suffixes[i].rank[1] = -1;
                }
                suffixes[i].index = i;
            }
            sort(suffixes.begin(), suffixes.end());
            REP(i, n){
                if(i > 0 and
		   suffixes[i].rank[0] == suffixes[i - 1].rank[0] and
		   suffixes[i].rank[1] == suffixes[i - 1].rank[1]){
                    __rmem[iteration][suffixes[i].index] =
			__rmem[iteration][suffixes[i - 1].index];
                } else {
                    __rmem[iteration][suffixes[i].index] = i;
                }
            }
        }
    }
};
