#include <vector>
using namespace std;

using ValueT = long long;
using SortT = int;
using Vector = vector<SortT>;

template<typename Comparator>
ValueT merge(Vector& toSort, Vector& helper, int low, int middle, int high, Comparator& comparator) {
    int i = low;
    int j = middle+1;
    int k = low;
    ValueT swaps{};

    while (i <= middle and j <= high) {
	if (comparator(toSort[i], toSort[j])) { // Comparator should answer if i < j
	    helper[k++] = toSort[i++];
	} else {
	    helper[k++] = toSort[j++];
	    swaps += (middle + 1 - i);
	}
    }

    while (i <= middle)
	helper[k++] = toSort[i++];

    while (j <= high)
	helper[k++] = toSort[j++];

    for (i = low; i <= high; i++)
	toSort[i] = helper[i];

    return swaps;
}

template<typename Comparator>
ValueT mergeSort(Vector& toSort, Vector& helper, int low, int high, Comparator& comparator) {
    if (low < high) {
	const int middle = (high + low) / 2;
	ValueT swaps = 0;
	swaps += mergeSort(toSort, helper, low, middle, comparator); 
	swaps += mergeSort(toSort, helper, middle+1, high, comparator);
	swaps += merge(toSort, helper, low, middle, high, comparator);
	return swaps;
    }
    return 0; // arrays of size <= 1 are already sorted
}

ValueT CountInversions(Vector& toSort) {
    Vector helper(toSort.size());
    struct Comp {
	bool operator()(SortT a, SortT b) const {
	    return a < b;
	}
    };
    Comp comp;
    return mergeSort(toSort, helper, 0, toSort.size() - 1, comp);
}

