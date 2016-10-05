// b^n % m in O(logy)
ll powmod(ll b, ll n, ll m) {
    ll res = 1;
    b = b % m;
    while (n > 0){
        if (n & 1){
            res = (res*b) % m;
        }
        n /= 2;
        b = (b * b) % m;
    }
    return res;
}
