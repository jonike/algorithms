/* Primality test using Miller-Rabin. */
#include <cstdlib>
using namespace std;

// (a ^ n) % m in O(log n).
template<typename T> T powmod(T a, T n, T m){
    T res = 1;
    a = a % m;
    while (n > 0){
        if (n & 1){
            res = (res * a) % m;
        }
        n /= 2;
        a = (a * a) % m;
    }
    return res;
}

template<typename T> bool miller_test(T d, T n){
    T a = 2 + rand() % (n - 4);
    T x = powmod(a, d, n);
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

// Returns true if n is a prime in O(k * log^3 n).
// Increase k to increase accuracy.
template<typename T> bool is_prime(T n, T k = 90000){
    if(n <= 1){
        return false;
    }
    if(n <= 3){
        return true;
    }
    if(n % 2 == 0 || n % 3 == 0){
        return false;
    }
    T d = n - 1;
    while(d % 2 == 0){
        d /= 2;
    }
    for(int i = 0; i < k; ++i){
        // If we use int instead of long long we will get overflow
        // (even for small primes).
        if(!miller_test<long long>(d, n)){
            return false;
        }
    }
    return true;
}
