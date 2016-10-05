/**
 * Uses Andrew's mono chain algorithm to solve the convex hull
 * problem. Tried using Graham scan first, but due to the nature of
 * that algorithm a bunch of special cases occur, making it way less
 * elegant.
*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <limits>
using namespace std;
typedef long long ValueT;
#define EPS 0
#define INF INT_MAX / 3
inline bool EQ(const ValueT& a, const ValueT& b){return a == b;}
struct point {
    ValueT x; ValueT y; point(ValueT _x, ValueT _y) : x(_x), y(_y){}
    point(){}
    bool operator==(const point& r) const {
	return EQ(x, r.x) && EQ(y, r.y);}
    bool operator<(const point& r) const {
	return x < r.x || (EQ(x, r.x) && y < r.y);}
};
ValueT cross(const point& a, const point& b, const point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);}


void mono_chain(vector<point>& pts, vector<point>& hull){
    // Remove duplicates.
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    // Init.
    const int n = pts.size();

    // Special case.
    if(n <= 2){
        hull = pts;
        return;
    }

    int k = 0;
    hull.resize(2 * n);

    // Upper part of hull.
    for(int i = 0; i < n; ++i){
	const auto tmp = cross(hull[k-2], hull[k-1], pts[i]);
        while(k >= 2 && tmp <= 0){
            --k;
        }
        hull[k] = pts[i];
        ++k;
    }

    // Lower part of hull.
    int t = k + 1;
    for(int i = n - 2; i >= 0; --i){
	const auto tmp = cross(hull[k-2], hull[k-1], pts[i]);
        while(k >= t && tmp <= 0){
            --k;
        }
        hull[k] = pts[i];
        ++k;
    }

    hull.resize(k - 1);
}
