/* Aho-Corasick string multimatching. */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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

    // Builds the Aho-Corasick state machine (basically a trie with a bunch of extra edges).
    // This can be prebuilt and then used to search many different texts.
    void RebuildStateMachine(const vector<string>& patterns){
        nodes.clear();
        nodes.push_back(CorasickNode()); // Start node.
        // Define states.
        for(unsigned int cp = 0; cp < patterns.size(); cp++){
            int n = 0;

            // Define a state for every char in the pattern with index cp.
            for(unsigned int i = 0; i < patterns[cp].size(); ++i){
                int& currentState = nodes[n].edges[toc(patterns[cp][i])];

                // Define all undefined states.
                if(currentState == -1){
                    currentState = nodes.size();
                    nodes.push_back(CorasickNode());
                }
                n = currentState;
            }
            nodes[n].matches.push_back(cp);
        }

        // Init BFS queue with all defined nodes that neighbour from the start node.
        // If an edge is undefined (i.e. it's not part of pattern), then point it back
        // at the start node.
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
                if(nodes[currentState].edges[c] != -1){ // Check if node is defined.

                    // Setup fail state by tracking through the fail states.
                    int failState = nodes[currentState].fail;
                    while(nodes[failState].edges[c] == -1){
                        failState = nodes[failState].fail;
                    }

                    // Init matches by checking the fail state.
                    nodes[nodes[currentState].edges[c]].fail = nodes[failState].edges[c];
                    for(int match : nodes[nodes[failState].edges[c]].matches){
                        nodes[nodes[currentState].edges[c]].matches.push_back(match);
                    }

                    // Push back defined edges on the queue and search those.
                    q.push(nodes[currentState].edges[c]);
                }
            }
        }
    }

    // Finds all occurences of all patterns in "patterns" in the text "text".
    // Stores first indices of the matches of pattern i in the "result[i]" vector.
    // Aho-Corasick search is worst case O(n + m + z) where n is size of text, m
    // size of pattern and z is number of occurences of pattern in the text.
    void FindMatches(const vector<string>& patterns, const string& text, vector<vector<int>>& results){
        int rootState = 0;
        for(unsigned int i = 0; i < text.length(); ++i){
            int currentState = rootState;
            int currentChar = toc(text[i]);

            // Goto is undefined => follow fail edge.
            while(nodes[currentState].edges[currentChar] == -1){
                currentState = nodes[currentState].fail;
            }
            nodes[rootState].edges[currentChar] = nodes[currentState].edges[currentChar];
            rootState = nodes[rootState].edges[currentChar];

            // Check for possible matches.
            for(auto j : nodes[rootState].matches){
                // Match at index i for pattern with index j!
                results[j].push_back(i - patterns[j].length() + 1);
            }
        }
    }
};
