typedef long long ll;

ll number_of_digits(ll x){
    return floor(log10(x)) + 1;
}

ll digit_at(ll p, ll x){
    while(p > 0){
        x /= 10;
        --p;
    }
    return x % 10;
}

ll powll(ll b, ll p){
    if(b == 0){
        return 0;
    }
    ll r = 1;
    while(p > 0){
        r *= b;
        --p;
    }
    return r;
}

ll most_significant_digit(ll x){
    while(x > 9){
        x /= 10;
    }
    return x % 10;
}

ll remove_most_significant_digit(ll x){
    ll temp = 0;
    ll ctr = 0;
    while(x > 9){
        temp += powll(10, ctr) * (x % 10);
        x /= 10;
        ++ctr;
    }
    return temp;
}

vector<ll> vectorize(ll x){
    vector<ll> vec;
    while(x > 0){
        vec.pb(x % 10);
        x /= 10;
    }
    return vec;
}
