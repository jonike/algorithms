#include <iostream>
#include <vector>
#include <algorithm>

#define pb        push_back
#define REP(k,a)  for(auto k=decltype(a)(0); k < (a); ++k)

using namespace std;
using vi=vector<int>;

// Finds all occurences of "pattern" in "text".
// Stores first indices of the matches in the "result" vector.
// KMP is O(n + m) in worst case.
vi KMPMatch(string& pattern, string& text){
    vi result;
    int m = pattern.size();
    int n = text.size();
    vector<int> LPS(m);
    int currentLength = 0;
    int i = 1, j = 0;

    // Construct longest proper suffix array to prevent
    // "jumping back" too far (or too short!) when we
    // have a mismatch or match.
    LPS[0] = 0;
    while(i < m){
        if(pattern[i] == pattern[currentLength]){
            currentLength++;
            LPS[i] = currentLength;
            i++;
        } else {
            if(currentLength != 0){
                currentLength = LPS[currentLength - 1];
            } else {
                LPS[i] = 0;
                i++;
            }
        }
    }

    // Find matches.
    i = 0;
    while(i < n){
        // Keep moving if we are matching. j is used to keep track of
        // number of current matches in pattern and i position in
        // text.
        if(pattern[j] == text[i]){
            j++;
            i++;
        }
        // Found a match that was m chars long => we have found a
        // complete match!
        if(j == m){
            result.pb(i - m);
            j = LPS[j - 1];
        } else if(i < n && pattern[j] != text[i]){
            // Mismatch!
            if(j != 0){
                j = LPS[j - 1];
            } else {
                i++;
            }
        }
    }
    return result;
}


