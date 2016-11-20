#include <vector>
using namespace std;

using vertex = pair<double, double>;

double cross(const vertex& v1, const vertex& v2) {
    return v1.first * v2.second - v1.second * v2.first;
}

// Returns the area of a given 2D polygon.
// The area is positive if the vertices are given in CW order,
// and negative if given in CCW order.
double area_of_polygon(const vector<vertex>& vertices) {
    double area = 0;
    for(int i = 0; i < vertices.size(); ++i){
        const vertex& v1 = vertices[i];
        const vertex& v2 = vertices[(i + 1) % vertices.size()];
        area += cross(v1, v2);
    }
    return area * 0.5;
}
