/**
@author Fredrik Präntare
@date 3/10/2016
Uses Andrew's mono chain algorithm to solve the convex hull problem.
Tried using Graham scan first, but due to the nature of that algorithm a bunch of special cases occur, making it way less elegant.
*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <limits>
using namespace std;
// --------------------------------------------------------------------------------
// Set these accordingly to adjust wether we are working with doubles, long long, int etc...
// Also remember to set input correctly (scanf currently so unformatted).
typedef long long val_type;
#define EPS 0
#define INF INT_MAX / 3
inline bool EQ(const val_type& a, const val_type& b){return a == b;}
// --------------------------------------------------------------------------------
struct point {
    val_type x; val_type y; point(val_type _x, val_type _y) : x(_x), y(_y){}
    point(){}
    bool operator==(const point& r) const {return EQ(x, r.x) && EQ(y, r.y);}
    bool operator<(const point& r) const {return x < r.x || (EQ(x, r.x) && y < r.y);}
};
val_type cross(const point& a, const point& b, const point& c){return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);}
// --------------------------------------------------------------------------------

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

    // Run mono chain algorithm.
    // Implementation pretty much the same as the one described here: https://en.m.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
    int k = 0;
    hull.resize(2 * n);

    // Upper part of hull.
    for(int i = 0; i < n; ++i){
        while(k >= 2 && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0){
            --k;
        }
        hull[k] = pts[i];
        ++k;
    }

    // Lower part of hull.
    int t = k + 1;
    for(int i = n - 2; i >= 0; --i){
        while(k >= t && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0){
            --k;
        }
        hull[k] = pts[i];
        ++k;
    }

    hull.resize(k - 1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while(cin >> n, n != 0){

        // Read pts.
        vector<point> pts;
        pts.reserve(n);
        for(int i = 0; i < n; ++i){
            val_type x, y;
            cin >> x >> y;
            pts.push_back(point(x,y));
        }

        // Find convex hull.
        vector<point> hull;
        mono_chain(pts, hull);

        // Print result.
        cout << hull.size() << endl;
        for(const auto& p : hull){
            // Remember that orientation is important!
            cout << p.x << " " << p.y << endl;
        }
    }
}
