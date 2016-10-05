#include <climits>
#include <limits>
#include <cstdlib>

using ll = long long:

// b^n % m in O(logy)
ll powmod(ll b, ll n, ll m){
    ll res = 1;
    b = b % m;
    while (n > 0){
        if (n & 1){
            res = (res * b) % m;
        }
        n /= 2;
        b = (b * b) % m;
    }
    return res;
}

bool miller_test(ll d, ll n){
    ll a = 2 + rand() % (n - 4);
    ll x = powmod(a, d, n);
    if (x == 1 || x == n - 1){
        return true;
    }
    while(d != n - 1){
        x = (x * x) % n;
        d *= 2;
        if(x == 1){return false;}
        if(x == n - 1){return true;}
    }
    return false;
}

// Returns true if n is a prime. k can be used to tweak accuracy.
bool is_prime(ll n, ll k = 9000){
    if(n <= 1 || n == 4){
        return false;
    }
    if(n <= 3){
        return true;
    }
    ll d = n - 1;
    while(d % 2 == 0){
        d /= 2;
    }
    for(int i = 0; i < k; ++i){
        if(!miller_test(d, n)){
            return false;
        }
    }
    return true;
}
