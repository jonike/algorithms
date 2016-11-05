/* Sieve of Eratosthenes. */
#include <vector>
using namespace std;

// Prime sieve in O(n * (log n) * (loglog n)).
template<typename T> vector<bool> sieve(T MAX_PRIME){
    vector<bool> p(++MAX_PRIME, true);
    p[0] = p[1] = false;
    for(int i = 2; i * i < MAX_PRIME; i++){
        if(p[i]){
            for(int j = i * i; j < MAX_PRIME; j += i){
                p[j] = false;
            }
        }
    }
    return p;
}
