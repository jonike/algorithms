#include <vector>
#include <tuple>
using namespace std;

using vi=vector<int>;

// Find the length maximal j such that seq[best[j]] < target
int binary_search(const vi& seq, const vi& best,
                  int low, int high, int target) {
  auto holds = [&](int a) {
    return seq[best[a]] < target;
  };

  for (int middle = (low+high)/2; high - low > 1; middle=(low+high)/2)
    holds(middle) ? low = middle : high = middle - 1;

  if (holds(high)) return high;
  else if (holds(low)) return low;
  else return 0; // Nothing is smaller than this (to the left)
}

// Returns the parent vector and the index to the last element in the
// longest sequence.
tuple<vi, int> LIS(const vi& seq) {
  int best_length = 1;
  vi current_best(seq.size() + 1);
  current_best[1] = 0;
  vi parent(seq.size());
  for (int i = 0; i < seq.size(); ++i) parent[i] = i;

  // For every number except the first one, find The maximum j such
  // that j < i && seq[j] < seq[i]. We do this by binary searching
  // over the length of the "previous" LIS. We keep a tab on where
  // each longest subsequence is by using the "current_best" vector.

  for (int i = 1; i < seq.size(); ++i) {
    int len = binary_search(seq, current_best, 1, best_length, seq[i]);

    if (len == 0) {
      parent[i] = i;
    } else {
      parent[i] = current_best[len];
    }

    const int len_with_this = len + 1;

    if (len_with_this > best_length ||
        seq[i] < seq[current_best[len_with_this]]) {
      current_best[len_with_this] = i;
      best_length = max(len_with_this, best_length);
    }
  }

  return tuple<vi, int>(parent, current_best[best_length]);
}

