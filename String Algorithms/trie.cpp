#include <vector>
#include <map>
#include <sstream>
using namespace std;

struct Node {
    char symbol{0};
    bool terminator{false};
    // This could also be of size 256 or similar and be a vector instead of map
    map<char, int> children;
    Node() {}
    Node(char k, bool t) : symbol{k}, terminator{t} {}
};

struct Trie {
    vector<Node> nodes;

    Trie() {
	nodes.push_back(Node{}); // Root node
    }

    /* Constructs missing nodes. */
    template<typename Func>
    void construct(const string& s, Func func, int start=0, int end=-1) {
	if (end == -1) end = s.size();
	int treeIdx = 0;
	for (int i = start; i < end; ++i) {
	    char sym = s[i];
	    const auto& node = nodes[treeIdx];
	    if (node.children.find(sym) == node.children.end()) {
		treeIdx = addNode(treeIdx, sym, i + 1 == end);
	    } else {
		treeIdx = node.children.at(sym);
	    }
	    func(nodes[treeIdx]);
	}
    }
    
    /* Walks the structure, without constructing anything. Returns true on reacing end of string. */
    template<typename Func>
    bool walk(const string& s, Func func, int start=0, int end=-1) {
	if (end == -1) end = s.size();
	int treeIdx = 0;
	for (int i = start; i < end; ++i) {
	    char sym = s[i];
	    const auto& node = nodes[treeIdx];
	    if (node.children.find(sym) == node.children.end()) {
		return false;
	    } else {
		treeIdx = node.children.at(sym);
		func(nodes[treeIdx]);
	    }
	}
	return true;
    }

    void addWord(const string& s) {
	construct(s, [](const Node&){});
    }

    int addNode(int parent, char c, bool terminates) {
	int nextIdx = nodes.size();
	nodes.push_back(Node{c, terminates});
	nodes[parent].children[c] = nextIdx;
	return nextIdx;
    }
    
    bool exists(const string& s) {
	int i = 0;
	bool isEnd = false;
	walk(s, [&](const Node& n) {if (++i == s.size()) isEnd=n.terminator;});
	return isEnd;
    }

    bool isPrefix(const string& s) {
	return walk(s, [](const Node&) {});
    }
    
    string longestPrefix(const string& s) {
	stringstream ss;
	walk(s, [&ss](const Node& n){ ss << n.symbol; });
	return ss.str();
    }

    vector<string> allPrefixes(const string& s) {
	vector<string> ret;
	stringstream ss;
	walk(s, [&ss, &ret](const Node& n) {
		ss << n.symbol;
		if (n.terminator) {
		    ret.push_back(ss.str());
		}
	    });
	return ret;
    }
    
};



