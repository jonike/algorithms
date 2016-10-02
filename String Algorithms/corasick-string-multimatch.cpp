/* Aho-Corasick string multimatching. */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using vvi=vector<vector<int>>;

const unsigned int ALPHABET_SIZE = 96;
inline int toc(char c){return c % ALPHABET_SIZE;}

// Represents a Corasick state machine.
struct CorasickStateMachine {
    // Represents a node in the Corasick trie.
    struct CorasickNode {
        int fail = 0; // Used to keep track on edge on fail.
        vector<int> matches;
        vector<int> edges;
        CorasickNode() : edges(vector<int>(ALPHABET_SIZE, -1)){}
    };

    vector<CorasickNode> nodes;

    // Builds the Aho-Corasick state machine (basically a trie with a
    // bunch of extra edges).  This can be prebuilt and then used to
    // search many different texts.
    void RebuildStateMachine(const vector<string>& patterns){
        nodes.clear();
        nodes.push_back(CorasickNode()); // Start node.
        for(unsigned int cp = 0; cp < patterns.size(); cp++){
            int n = 0;

            // State for every char in the pattern with index cp.
            for(unsigned int i = 0; i < patterns[cp].size(); ++i){
		const auto tmp = toc(patterns[cp][i]);
                int& currentState = nodes[n].edges[tmp];

                // Define all undefined states.
                if(currentState == -1){
                    currentState = nodes.size();
                    nodes.push_back(CorasickNode());
                }
                n = currentState;
            }
            nodes[n].matches.push_back(cp);
        }

        // Init BFS queue with all defined nodes that neighbour from
        // the start node.  If an edge is undefined (i.e. it's not
        // part of pattern), then point it back at the start node.
        queue<int> q;
        for(unsigned int c = 0; c < ALPHABET_SIZE; ++c){
            if(nodes[0].edges[c] > 0){
                q.push(nodes[0].edges[c]); // Search node.
            } else if(nodes[0].edges[c] == -1){
                nodes[0].edges[c] = 0; // Point back at start node.
            }
        }

        // Start BFS to find and add/initialize failure edges.
        while(!q.empty()){
            int currentState = q.front(); q.pop();
            for(unsigned int c = 0; c < ALPHABET_SIZE; ++c){
                if(nodes[currentState].edges[c] != -1){

                    int failState = nodes[currentState].fail;
                    while(nodes[failState].edges[c] == -1){
                        failState = nodes[failState].fail;
                    }

		    const auto& edge = nodes[currentState].edges[c];
                    nodes[edge].fail = nodes[failState].edges[c];
                    for(int match : nodes[edge].matches){
                        nodes[edge].matches.push_back(match);
                    }

                    q.push(edge);
                }
            }
        }
    }

    // Finds all occurences of all patterns in "patterns" in the text
    // "text". Stores first indices of the matches of pattern i in the
    // "result[i]" vector. Aho-Corasick search is worst case O(n + m +
    // z) where n is size of text, m size of pattern and z is number
    // of occurences of pattern in the text.
    void FindMatches(const vector<string>& patterns,
		     const string& text, vvi& results){
        int rootState = 0;
        for(unsigned int i = 0; i < text.length(); ++i){
            int currentState = rootState;
            int currentChar = toc(text[i]);

            // Goto is undefined => follow fail edge.
            while(nodes[currentState].edges[currentChar] == -1){
                currentState = nodes[currentState].fail;
            }
	    
	    const auto& curr = nodes[currentState].edges[currentChar];
            nodes[rootState].edges[currentChar] = curr;
            rootState = nodes[rootState].edges[currentChar];

            for(auto j : nodes[rootState].matches){
                // Match at index i for pattern with index j!
                results[j].push_back(i - patterns[j].length() + 1);
            }
        }
    }
};
