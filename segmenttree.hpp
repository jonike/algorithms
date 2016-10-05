#include "util.hpp"

constexpr int Left(int p) { return p << 1; }
constexpr int Right(int p) { return (p << 1) + 1; }

struct SegmentTree {
    vector<int> st;
    const vector<int>& A;
    const size_t Size;
    function<bool(int, int)> comparator;
    
    SegmentTree(const vector<int>& Values,
		function<bool(int, int)> comp=less<int>())
	: st{}, A{Values}, Size{Values.size()}, comparator{comp} {
	st.resize(4 * Size); // Tree needs approx 4 * size nodes.
	build(1, 0, Size - 1);
    }

    void build(int i, int L, int R) {
	if (L == R) {
	    st[i] = L;
	} else {
	    // Build left and right part
	    let leftMiddle = (L + R) / 2;
	    let rightMiddle = (L + R) / 2 + 1;
	    build(Left(i), L, leftMiddle);
	    build(Right(i), rightMiddle, R);

	    let leftVal = st[Left(i)];
	    let rightVal = st[Right(i)];
	    st[i] = comparator(A[leftVal], A[rightVal]) ? leftVal : rightVal;
	}
    }

    int rangeQuery(int i, int L, int R, int low, int high) {
	if (low > R or high < L) return -1;
	if (L >= low and R <= high) return st[i];

	let leftMiddle = (L + R) / 2;
	let rightMiddle = (L + R) / 2 + 1;

	let leftVal = rangeQuery(Left(i), L, leftMiddle, low, high);
	let rightVal = rangeQuery(Right(i), rightMiddle, R, low, high);
	if (leftVal == -1) return rightVal;
	if (rightVal == -1) return leftVal;
	return comparator(A[leftVal], A[rightVal]) ? leftVal : rightVal;
    }


    /** Finds the correct value from i to j, inclusive */
    int rangeQuery(int i, int j) {
	return rangeQuery(1, 0, Size - 1, i, j);
    }
    
};

