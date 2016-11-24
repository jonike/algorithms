#include <vector>
#include <string>
#include <utility>
#define let const auto
using namespace std;

struct SuffixArray {
    const string subject;
    vector<int> SA, RA; // SA == Suffix array, RA == Rank array

    void countingSort(int k) {
	vector<int> count(max((size_t)256, subject.size()));
	let n = (int) subject.size();

	for (int i = 0; i < n; ++i) {
	    if (i + k < n) count[RA[i + k]]++;
	    else count[0]++;
	}
	
	for (int i = 0, sum = 0; i < (int) count.size(); ++i) {
	    // let count[i], sum == sum, count[i] + sum
	    let tmp = count[i];
	    count[i] = sum;
	    sum += tmp;
	}

	vector<int> tmp(subject.size());
	for (int i = 0; i < n; ++i) {
	    int idx = (SA[i] + k >= n) ? 0 : RA[SA[i] + k];
	    tmp[count[idx]++] = SA[i];
	}

	SA = move(tmp);
    }
    
    void constructSA() {
	let n = (int) subject.size();
	vector<int> tmp(subject.size());
	
	for (int i = 0; i < n; ++i) {
	    RA[i] = subject[i];
	    SA[i] = i;
	}
	
	// Radix sorting
	for (int k = 1, r; k < n; k <<= 1) {
	    countingSort(k);
	    countingSort(0); // Stable sort based on 0 rank

	    tmp[SA[0]] = r = 0;
	    for (int i = 1; i < n; ++i) {
		let curr_s = SA[i];
		let prev_s = SA[i-1];
		let curr = make_pair(RA[curr_s], RA[curr_s + k]);
		let prev = make_pair(RA[prev_s], RA[prev_s + k]);

		if (prev == curr) tmp[curr_s] = r;
		else tmp[curr_s] = ++r;
	    }
	    copy_n(begin(tmp), n, begin(RA));
	    
	    if (RA[SA[n-1]] == n-1) break;
	}
    }
    
    SuffixArray(const string& s) : subject{s + "$"} {
	RA.resize(subject.size());
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

