/* Convex hull using Andrew's monotone chain algorithm in O(n log n). */
#include <vector>
#include <algorithm>
using namespace std;

// If using float or double: make sure that the equals (==) operator
// is correct.
using value_type = int;

struct point{
    value_type x, y; 
    point(value_type _x, value_type _y) : x(_x), y(_y){}
    point(){}
    bool operator==(const point & r) const
    {return x == r.x && y == r.y;}
    bool operator<(const point & r) const
    {return x < r.x || (x == r.x && y < r.y);}
    static value_type cross(const point & a, const point & b, const point & c){
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
};

vector<point> convex_hull(vector<point> pts){ // Note! Copied, not referenced!
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
	
    const int n = pts.size();
    if(n <= 2){ return pts; }
    vector<point> hull(2 * n);

    int k = 0;
    for(int i = 0; i < n; ++i){
        while(k >= 2 && point::cross(hull[k-2], hull[k-1], pts[i]) <= 0){
            --k;
        }
        hull[k++] = pts[i];
    }

    for(int i = n - 2, t = k + 1; i >= 0; --i){
        while(k >= t && point::cross(hull[k-2], hull[k-1], pts[i]) <= 0){
            --k;
        }
        hull[k++] = pts[i];
    }

    hull.resize(k - 1);
    return hull;
}
