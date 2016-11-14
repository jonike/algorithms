/* Calculates the Euler-Phi totient function for a given number. */
#include <algorithm>
#define MAX_PRIME 10000000
using namespace std;

using ull = unsigned long long;

bool is_prime[MAX_PRIME + 1];

// Call this once first.
void sieve(){
    is_prime[0] = false;
    is_prime[1] = false;
    for(ull i = 2; i <= MAX_PRIME; ++i){
        is_prime[i] = true;
    }
    for(ull i = 2; i * i <= MAX_PRIME; ++i){
        if(is_prime[i]){
            for(ull j = i * i; j <= MAX_PRIME; j += i){
                is_prime[j] = false;
            }
        }
    }
}

// Counts the positive integers up to a given integer x that are relatively prime to x.
// See https://en.wikipedia.org/wiki/Euler%27s_totient_function
ull euler_phi(ull x){
    if(x <= MAX_PRIME && is_prime[x]){ return x - 1; }
    ull res = x;
    for(size_t i = 2; i * i <= x; ++i){
        if(x % i == 0){
            res -= res / i;
            while(x % i == 0){ x /= i; }
        }
    }
    if(x > 1){ res -= res / x; }
    return res;
}
