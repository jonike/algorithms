long long fact(long long n){
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;}
long long permutations(long long n, long long k){
    return factorial_dp(n) / factorial_dp(n - k);}
long long combinations(long long n, long long k){
    return factorial_dp(n) / (factorial_dp(k) * factorial_dp(n - k));}
