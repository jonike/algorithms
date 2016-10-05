#include <map>
#include <vector>
#include <set>
using namespace std;

#define MAX_PRIME 10000

int main(){
    // Generate on the interval [0, MAX_PRIME).
    vector<bool> isPrime(MAX_PRIME, true);
    for(int i = 2; i * i < MAX_PRIME; i++){
        if(isPrime[i]){
            for(int j = i * i; j < MAX_PRIME; j += i){
                isPrime[j] = false;
            }
        }
    }
}
