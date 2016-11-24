#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <cstring>
#define let const auto
using namespace std;

struct SuffixArray {
    const string subject;
    vector<int> SA;

    struct entry {
	pair<int, int> nr;
	int pos;

	bool operator<(const entry& e) {
	    return nr < e.nr;
	}
    };

    
    void constructSA() {
	let n = (int) subject.size();
	vector<entry> L(n);
	vector< vector<int> > P;
	P.push_back(vector<int>(n));
	for (int i = 0; i < n; ++i) {
	    P[0][i] = subject[i];
	}
	
	for (int k = 1, cnt = 1; cnt >> 1 < n; ++k, cnt <<= 1) {
	    for (int i = 0; i < n; ++i) {
		L[i] = {make_pair(P[k-1][i], (i + cnt < n) ? P[k-1][i+cnt] : -1), i};
	    }
	    sort(begin(L), end(L));
	    vector<int> Papp(n);
	    for (int i = 1; i < n; ++i) {
		Papp[L[i].pos] = (L[i].nr == L[i - 1].nr) ? Papp[L[i - 1].pos] : i;
	    }

	    P.push_back(Papp);
	}

	for (int i = 0; i < n; ++i) {
	    SA[P[P.size() - 1][i]] = i;
	}
    }
    
    
    SuffixArray(const string& s) : subject{s} {
	SA.resize(subject.size());
	constructSA();
    }

    int compare(int idx, const string& pattern) {
	return strncmp(subject.c_str() + SA[idx], pattern.c_str(), pattern.size());
    }
    
    /* Returns lower and upper bound in SA for the matching. 
       That is: for all i in [lower, upper) the pattern matches subject[i:] */
    pair<int, int> FindSAMatches(const string& pattern) {
	// Do two binary searches in one loop. One for lower bound, one for upper bound. 
	int low_l = 0, low_u = 0; // suffix _l means lower and _u means upper
	int high_l = SA.size()-1, high_u = SA.size()-1;
	while (low_l < high_l or low_u < high_u) {
	    if (low_l < high_l) {
		let mid_l = low_l + (high_l - low_l) / 2;
		let res_l = compare(mid_l, pattern);
		if (res_l >= 0)  high_l = mid_l;
		else low_l = mid_l + 1;
	    }
	    if (low_u < high_u) {
		let mid_u = low_u + (high_u - low_u) / 2;
		let res_u = compare(mid_u, pattern);
		if (res_u > 0) high_u = mid_u;
		else low_u = mid_u + 1;
	    }
	}

	if (compare(low_l, pattern) != 0)
	    return pair<int, int>{-1, -1}; // Non-existant match

	/* There is an edge case for pattern at the end of the suffix array. 
	   upper bound cannot "normally" be size() */
	high_u += compare(high_u, pattern) == 0;
	return pair<int, int>{low_l, high_u};
    }

    /* Returns all the indices where pattern matches. */
    vector<int> FindMatches(const string& pattern) {
	let bounds = FindSAMatches(pattern);
	vector<int> ret{}; // Y U no list builders??!!
	for (int low = bounds.first; low < bounds.second; ++low) {
	    ret.push_back(SA[low]);
	}
	return ret;
    }
};

