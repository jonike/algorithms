/*
@author Fredrik Präntare
@date 3/3/2016
Solves the modular arithmetic problem on Kattis.
References:
https://en.wikipedia.org/wiki/Modular_arithmetic
https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
http://www.math.utah.edu/~fguevara/ACCESS2013/Euclid.pdf
http://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
*/

#include <iostream>
#include <vector>

#include <algorithm>

#define sl(n)                       scanf("%lld",&n)
#define si(n)                       scanf("%d",&n)

// Do stuff.
#define pb                          push_back
#define mp                          make_pair
#define REP(k,a)                    for(auto k=decltype(a)(0); k < (a); ++k)

using namespace std;
typedef long long lint;

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// Returns the modulus of a number and handles negative numbers too.
lint negmod(lint a, lint n){
    return (n + (a % n)) % n;
}

// Simple greatest common divisor algorithm. Doesn't handle much but
// can be used to determine if a and b are coprime.
lint gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}

// Extended version of gcd that can be used to calculate the multiplicative inverse .
lint gcdext(lint a, lint b, lint* x, lint* y){
    if(a == 0){
        *x = 0;
        *y = 1;
        return b;
    } else {
        lint _x, _y;
        lint g = gcdext(b % a, a, &_x, &_y);
        *x = _y - (b / a) * _x;
        *y = _x;
        return g;
    }
}

// Calculates the inverse multiplicative iteratively.
// -1 if inverse doesn't exist.
lint modinviter(lint a, lint n)
{
    if(gcd(a, n) != 1){
        return -1; // Not coprime.
    }
    lint n0 = n, t, q, x0 = 0, x1 = 1;
    if (n == 1){
        return 0;
    }
    while (a > 1){
        q = a / n;
        t = n;
        n = a % n;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0){
        x1 += n0;
    }
    return x1;
}

// Calculates the modular multiplicative inverse (https://en.wikipedia.org/wiki/Modular_multiplicative_inverse)
// -1 if inverse doesn't exist.
lint modinv(lint a, lint n){
    lint ainv, scrap;
    lint g = gcdext(a, n, &ainv, &scrap);
    if(g != 1){
        return -1; // Inverse doesn't exist.
    } else {
        return negmod(ainv, n);
    }
}

// Calculates (a + b) mod n.
// Input requirement: a >= 0 && b >= 0.
lint add(lint a, lint b, lint n){
    return (a + b) % n;
}

// Calculates (a - b) mod n.
// Input requirement: a >= 0 && b >= 0.
lint diff(lint a, lint b, lint n){
    lint d = a - b;
    if(d < 0){
        return negmod(d, n);
    } else {
        return d % n;
    }
}

// Calculates (a * b) mod n.
// Input requirement: a >= 0 && b >= 0.
lint mul(lint a, lint b, lint n){
    return ((a % n) * (b % n)) % n;
}

// Calculates (a * b^-1) mod n where b^-1 is the modular multiplicative inverse
// of b.
// Input requirement: a >= 0 && b >= 0.
lint div(lint a, lint b, lint n){
    lint binv = modinv(b, n);
    if(binv == -1){
        return -1;
    } else {
        return mul(a, binv, n);
    }
}

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);
    while(true){
        lint n, m;
        sl(n);
        sl(m);
        if(n == 0 && m == 0){
            return 0;
        }
        lint x, y;
        char op;
        REP(i, m){
            scanf("%lld %c %lld", &x, &op, &y);
            if(op == '/'){
                // printf("div ");
                printf("%lld\n", div(x, y, n));
            } else if(op == '*'){
                // printf("mul ");
                printf("%lld\n", mul(x, y, n));
            } else if(op == '-'){
                // printf("dif ");
                printf("%lld\n", diff(x, y, n));
            } else if(op == '+'){
                // printf("add ");
                printf("%lld\n", add(x, y, n));
            }
        }
    }
}
