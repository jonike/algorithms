#include <vector>
#include <string>
using namespace std;

struct Range {
    struct Iterator {
    int i;
    bool operator!=(Iterator& rhs) {
        return i != rhs.i;
    }
    Iterator& operator++() {
        i++;
        return *this;
    }
    int operator*() {
        return i;
    }
    
    };

    int a, b;

    Range(int a) : a{}, b{a} {}
    Range(int a, int b) : a{a}, b{b} {}
    Iterator begin() {
        return Iterator{a};
    }

    Iterator end() {
        return Iterator{b};
    }
};

vector<int> BuildKMPTable(const string& pattern) {
    let sz = (int) pattern.size();
    
    vector<int> table(pattern.size() + 1);
    table[0] = -1;
    int pos = 0, cnd = -1;

    while (pos < sz) {
        while (cnd >= 0 && pattern[cnd] != pattern[pos]) {
            cnd = table[cnd];
        } // Jump back until found match
        pos++; cnd++;
        table[pos] = (pattern[pos] == pattern[cnd]) ? table[cnd] : cnd;
    }

    return table;
}

vector<int> KMPSearch(const string& pattern, const string& text) {
    vector<int> indices;
    
    let table = BuildKMPTable(pattern);
    let sz = (int) pattern.size();
    int i = 0;

    for (let pos : Range(text.size())) {
        while (i >= 0 && text[pos] != pattern[i]) {
            i = table[i];
        } // Jump back until text matches
        i++;
        if (i >= sz) {
            indices.push_back(pos - i + 1);
            i = table[i];
        }
    }

    return indices;
}
