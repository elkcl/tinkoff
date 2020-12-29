#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

struct Point {
    double x;
    double y;
    double absv();
    Point norm();
};

Point operator+(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator*(Point a, double k) {
    return {a.x * k, a.y * k};
}

Point operator*(double k, Point a) {
    return {a.x * k, a.y * k};
}

Point operator/(Point a, double k) {
    return {a.x / k, a.y / k};
}

double operator*(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double operator%(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double Point::absv() {
    return sqrt((*this) * (*this));
}

Point Point::norm() {
    return (*this) / this->absv();
}

struct Line {
    Point n;
    Point p;
    Line(Point a, Point b) {
        p = a;
        n = (b - a).norm();
    }
    bool contains(Point a) const;
};

Point perp(Point p, Line l) {
    Point v = l.p - p;
    return v - (l.n * v) * l.n;
}

bool Line::contains(Point a) const {
    return (p - a) % n == 0;
}

struct Segment {
    Point a;
    Point b;
    Line l;
    Segment(Point p1, Point p2): a{p1}, b{p2}, l{p1, p2} {}
    bool contains(Point p) const;
};

bool Segment::contains(Point p) const {
    return l.contains(p) && (a - p) * (b - p) <= 0;
}

double distance(Point p, Segment s) {
    Point pe = perp(p, s.l);
    if(s.contains(pe + p)) {
        return pe.absv();
    } else {
        return min((s.a - p).absv(), (s.b - p).absv());
    }
}

struct Ray {
    Point a;
    Point b;
    Line l;
    Ray(Point p1, Point p2): a{p1}, b{p2}, l{p1, p2} {}
    bool contains(Point p) const;
};

bool Ray::contains(Point p) const {
    return l.contains(p) && ((a - p) * (b - p) <= 0 || (a - b) * (p - b) <= 0);
}

double distance(Point p, Ray r) {
    Point pe = perp(p, r.l);
    if(r.contains(pe + p)) {
        return pe.absv();
    } else {
        return (r.a - p).absv();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout.setf(ios::fixed);
    cout.precision(7);

    Point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y
        >> c.x >> c.y >> d.x >> d.y;
    Segment sAB(a, b);
    Ray rAB(a, b);
    Segment sCD(c, d);
    Ray rCD(c, d);

    cout << (c - a).absv() << '\n'
         << distance(a, sCD) << '\n'
         << distance(a, rCD) << '\n'
         << perp(a, sCD.l).absv() << '\n'
         ;
}