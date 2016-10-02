/* Decides whether a point is inside a 2D polygon or not. */
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

using vertex = pair<double, double>;

bool DEQ(double a, double b) {
    return abs(a - b) < 0.000000000001;
}
double dot(const vertex& l, const vertex& r) {
    return l.first * r.first + l.second * r.second;
}
double cross(const vertex& v1, const vertex& v2) {
    return v1.first * v2.second - v1.second * v2.first;
}
double dist(const vertex& a, const vertex& b){
    return sqrt((a.first - b.first) * (a.first - b.first) +
		(a.second - b.second) * (a.second - b.second));
}
double angle_of(const vertex& p, const vertex& a,
		const vertex& b) {
    const vertex v1(a.first - p.first, a.second - p.second);
    const vertex v2(b.first - p.first, b.second - p.second);
    return atan2(cross(v1, v2), dot(v1, v2));
}

// Returns 1 if point is inside the polygon.
// Returns 0 if the point is on the border of the polygon.
// Returns -1 if the point is outside of the polygon.
int point_in_polygon(const vector<vertex>& vertices,
		     const vertex& p){
    double angle = 0;
    for (int i = 0; i < vertices.size(); ++i) {
        const vertex& v1 = vertices[i];
        const vertex& v2 = vertices[(i + 1) % vertices.size()];
        double d1 = dist(v1, p);
        double d2 = dist(v2, p);
        double d = dist(v1, v2);
        if (DEQ(d1 + d2, d)) {
            return 0;
        }
        angle += angle_of(p, v1, v2);
    }
    if (abs(angle) > 3.141592653589793238 / 2.0) {
        return 1;
    } else {
        return -1;
    }
}
