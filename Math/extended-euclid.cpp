#include <tuple>
using namespace std;

using ValueT = int;

ValueT GCD(ValueT a, ValueT b) {
    if (b == 0) return a;
    return GCD(b, a%b);
}

ValueT LCM(ValueT a, ValueT b) {
    return abs(a*b) / GCD(a, b);
}

using i3tuple = tuple<ValueT, ValueT, ValueT>;
using i2tuple = tuple<ValueT, ValueT>;
const i2tuple IMPOSSILBE = i2tuple{-1, -1};

i3tuple ExtendedEuclid(ValueT a, ValueT b) {
    if (a == 0) return i3tuple(b, 0, 1);
    ValueT gcd, x, y;
    tie(gcd, x, y) = ExtendedEuclid(b % a, a);
    return i3tuple{gcd, x - (b/a) * y, y};
}

i2tuple DiophanticEquation(ValueT a, ValueT b, ValueT c) {
    if (c%GCD(a, b) != 0) return i2tuple{-1, -1};
    ValueT gcd, x, y;
    tie(gcd, x, y) = ExtendedEuclid(a, b);
    return i2tuple{x * c, y * c};
}
