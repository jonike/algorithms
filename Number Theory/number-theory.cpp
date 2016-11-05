/*  Helpers for number theoretical problems:
    - egcd (Extended Euclidean Algorithm).
    - gcd (Greatest Common Divisor).
    - lcm (Least Common Multiple).
    - negmod (Negative Modulus).
    - modinv (Modular Multiplicative Inverse).
    - powmod (Modular Exponentiation).
    - miller_test (Miller Test).
    - is_prime (Prime Test using Miller Test).
    - sieve (Simple Prime Sieve).
*/
#include <cstdlib>
#include <vector>
using namespace std;

// Returns (g, x, y) such that ax + by = g = gcd(a, b).
template<typename T> T egcd(T a, T b, T * x, T * y){
    if(a == 0){
        *x = 0;
        *y = 1;
        return b;
    } else {
        T _x, _y;
        T g = egcd(b % a, a, &_x, &_y);
        *x = _y - (b / a) * _x;
        *y = _x;
        return g;
    }
}

template<typename T> T gcd(T a, T b) {return b == 0 ? a : gcd<T>(b, a % b);}
template<typename T> T lcm(T a, T b) {return abs(a * b) / gcd(a, b);}
template<typename T> T negmod(T a, T n){if(a < 0){return (n + (a % n)) % n;} else {return a;}}
template<typename T> T modinv(T a, T n){T ainv, scrap;egcd(a, n, &ainv, &scrap);return negmod(ainv, n);}

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
    if(n % 2 == 0){
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
