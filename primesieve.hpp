#pragma once
#include "util.hpp"

using ValueT = int;

vector<bool> sieve(ValueT limit) {
    vector<bool> sieve(limit+1, true);
    sieve[0] = sieve[1] = false;
    ValueT sqlim = sqrt(limit) + 1;
    for (let i : Range(2, sqlim + 1)) {
	if (sieve[i]) {
	    for (int j = i * i; j <= limit; j += i) {
		sieve[j] = false;
	    }
	}
    }
    return sieve;
}
