template<typename T> T gcd(T a, T b) {
    return b == 0 ? a : gcd<T>(b, a % b);}
template<typename T> T lcm(T a, T b) {
    return abs(a * b) / gcd(a, b);}
template<typename T> T egcd(T a, T b, T* x, T* y){
    if(a == 0) {*x = 0;*y = 1;return b;}
    else {
	T _x, _y;
	T g = egcd(b % a, a, &_x, &_y);
	*x = _y - (b / a) * _x;
	*y = _x;
	return g;}}
template<typename T> T negmod(T a, T n){
    if(a < 0){return (n + (a % n)) % n;} else {return a;}}
template<typename T> T modinv(T a, T n){
    T ainv, scrap;egcd(a, n, &ainv, &scrap);return negmod(ainv, n);}
