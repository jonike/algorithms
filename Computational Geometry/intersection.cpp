#include <cmath>
#define let const auto
using namespace std;

using T = double;

struct Point {
    T x, y;
    Point() : x{}, y{} {}
    Point(T a, T b): x{a}, y{b} {}
};

struct Line {
    /* A line on the form ax + by + c = 0 */
    double a, b, c;
    Line() : a{}, b{}, c{} {}
    Line(double p, double u, double v) : a{p}, b{u}, c{v} {}
};

struct Circle {
    double x, y, r;
    Circle() : x{}, y{}, r{} {}
    Circle(double a, double b, double c) : x{a}, y{b}, r{c} {}
};

/* Treat point as vector, calculate magnitude. */
double magnitude(const Point& p) {
    return sqrt(p.x*p.x + p.y*p.y);
}

double dist(const Point& p, const Point& q) {
    return magnitude({p.x - q.x, p.y - q.y});
}

constexpr bool EPS(double d) { return abs(d) < 0.0000001; }

Line pointsToLine(const Point& p, const Point& q) {
    double a, b, c;
    a = p.y - q.y;
    b = q.x - p.x;
    c = (p.x * q.y - q.x * p.y);
    return Line(a, b, c);
}

bool pointOnLine(const Line& l, const Point& p) {
    return EPS(l.a * p.x + l.b * p.y + l.c);
}

double dot(const Point& p, const Point& q) {
    return p.x * q.x + p.y * q.y;
}

/* Finds the closest point on l to p. */
Point closestPoint(const Line& l, const Point& p) {
    let n = Point{l.a, l.b};
    let s = - (l.c + dot(n, p)) / dot(n, n);
    return Point{p.x + s * l.a, p.y + s * l.b};
}

bool intersects(const Line& l, const Circle& c) {
    let close = closestPoint(l, {c.x, c.y});
    /* Double check that <= is actually what you want */
    return dist(close, {c.x, c.y}) <= c.r;
}

bool intersection(const Line& l1, const Line& l2, Point& ret) {
    // parallell
    if (EPS(l1.a - l2.a) and EPS(l1.b - l2.b)) return false;
    // Assuming l1.a != 0!!!
    
    // a1*x + b1*y + c1 = 0
    // a2*x + b2*y + c2 = 0

    // a1*x = -(c1 + b1*y)
    // x = -(c1 + b1*y) / a1

    // a2 (- c1 - b1 * y) / a1 + b2*y + c2 = 0
    // (a2 (- c1 - b1)/a1 + b2) y = - c2

    let k = (l2.a * (-l1.c - l1.c) / l1.a + l2.b);
    let y = -l2.c / k;
    let x = -(l1.c + l1.b*y) / l1.a;
    ret.x = x; ret.y = y;
    return true;
}

