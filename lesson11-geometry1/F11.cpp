#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

const ld EPS = 1e-10;

int sgn(ld val) {
    return (0 < val) - (val < 0);
}

struct Point {
    ld x;
    ld y;
    ld absv() const;
    Point norm() const;
    Point rotate(ld a) const;
};

Point operator+(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator*(Point a, ld k) {
    return {a.x * k, a.y * k};
}

Point operator*(ld k, Point a) {
    return {a.x * k, a.y * k};
}

Point operator/(Point a, ld k) {
    return {a.x / k, a.y / k};
}

ld operator*(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

ld operator%(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool operator==(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

ld angle(Point a, Point b) {
    return atan2(a % b, a * b);
}

ld Point::absv() const {
    return sqrt((*this) * (*this));
}

Point Point::norm() const {
    return (*this) / this->absv();
}

Point Point::rotate(ld a) const {
    return {
            cos(a) * x - sin(a) * y,
            sin(a) * x + cos(a) * y
    };
}

ld distance(Point p1, Point p2) {
    return (p2 - p1).absv();
}

struct Line {
    Point n{};
    Point p{};
    Line(Point a, Point b) {
        p = a;
        n = (b - a).norm();
    }
    Line(ld a, ld b, ld c) {
        n = Point{-b, a}.norm();
        if (b == 0) {
            p = {-c / a, 0};
        } else {
            p = {0, -c / b};
        }
    }
    bool contains(Point a) const;
    int halfPlane(Point p1) const;
};

Point perp(Point p, Line l) {
    Point v = l.p - p;
    return v - (l.n * v) * l.n;
}

bool Line::contains(Point a) const {
    return abs((p - a) % n) < EPS;
}

bool operator||(Line a, Line b) {
    return abs(a.n % b.n) < EPS;
}

bool operator==(Line a, Line b) {
    return a.contains(b.p) && (a || b);
}

pair<Point, int> operator^(Line a, Line b) {
    if (a == b) {
        return {a.p, 2};
    } else if (a || b) {
        return {a.p, 0};
    } else {
        ld k = (a.n % b.n);
        ld x = (b.n.x * (a.n % a.p) - a.n.x * (b.n % b.p)) / k;
        ld y = (b.n.y * (a.n % a.p) - a.n.y * (b.n % b.p)) / k;
        return {{x, y}, 1};
    }
}

int Line::halfPlane(Point p1) const {
    return sgn(n % (p1 - p));
}

ld distance(Point p, Line l) {
    return perp(p, l).absv();
}

struct Segment {
    Point a;
    Point b;
    Line l;
    Segment(Point p1, Point p2): a{p1}, b{p2}, l{p1, p2} {}
    bool contains(Point p) const;
};

bool Segment::contains(Point p) const {
    return l.contains(p) && (a - p) * (b - p) <= EPS;
}

ld distance(Point p, Segment s) {
    Point pe = perp(p, s.l);
    if (s.contains(pe + p)) {
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
    return l.contains(p) && ((a - p) * (b - p) <= EPS || (a - b) * (p - b) <= EPS);
}

ld distance(Point p, Ray r) {
    Point pe = perp(p, r.l);
    if (r.contains(pe + p)) {
        return pe.absv();
    } else {
        return (r.a - p).absv();
    }
}

ld distance(Line l1, Line l2) {
    int res = (l1 ^ l2).second;
    if (res == 1 || res == 2) {
        return 0;
    } else {
        return distance(l1.p, l2);
    }
}

ld distance(Ray r, Line l) {
    auto inter = r.l ^ l;
    if (inter.second == 2 ||
        (inter.second == 1 && r.contains(inter.first))) {
        return 0;
    } else {
        return distance(r.a, l);
    }
}

ld distance(Segment s, Line l) {
    auto inter = s.l ^ l;
    if (inter.second == 2 ||
        (inter.second == 1 && s.contains(inter.first))) {
        return 0;
    } else {
        return min(distance(s.a, l), distance(s.b, l));
    }
}

ld distance(Ray r1, Ray r2) {
    auto inter = r1.l ^ r2.l;
    if (inter.second == 2) {
        if (r1.contains(r2.a) || r2.contains(r1.a)) {
            return 0;
        } else {
            return distance(r1.a, r2.a);
        }
    } else if (inter.second == 1 && r1.contains(inter.first) && r2.contains(inter.first)) {
        return 0;
    } else {
        return min(distance(r1.a, r2), distance(r2.a, r1));
    }
}

ld distance(Segment s, Ray r) {
    auto inter = s.l ^ r.l;
    if (inter.second == 2) {
        if (r.contains(s.a) || r.contains(s.b)) {
            return 0;
        } else {
            return min(distance(s.a, r.a), distance(s.b, r.a));
        }
    } else if (inter.second == 1 && s.contains(inter.first) && r.contains(inter.first)) {
        return 0;
    } else {
        return min(min(distance(s.a, r), distance(s.b, r)), distance(r.a, s));
    }
}

ld distance(Segment s1, Segment s2) {
    auto inter = s1.l ^ s2.l;
    if (inter.second == 2) {
        if (s1.contains(s2.a) || s1.contains(s2.b) || s2.contains(s1.a) || s2.contains(s1.b)) {
            return 0;
        } else {
            return min(distance(s1.a, s2), distance(s1.b, s2));
        }
    } else if (inter.second == 1 && s1.contains(inter.first) && s2.contains(inter.first)) {
        return 0;
    } else {
        return min(min(distance(s1.a, s2), distance(s1.b, s2)), min(distance(s2.a, s1), distance(s2.b, s1)));
    }
}

struct Triangle {
    Point a;
    Point b;
    Point c;
    bool contains(Point p) const;
};

bool Triangle::contains(Point p) const {
    ld p1 = (b - a) % (p - a);
    ld p2 = (c - b) % (p - b);
    ld p3 = (a - c) % (p - c);
    return p1 >= -EPS && p2 >= -EPS && p3 >= -EPS;
}

struct ConvexPolygon {
    vector<Point> vs;
    vector<ld> angles;
    ConvexPolygon(vector<Point> &av): vs{av} {
        angles.resize(vs.size());
        angles[0] = angles[1] = 0;
        Point base = vs[1] - vs[0];
        for (int i = 2; i < vs.size(); ++i) {
            angles[i] = angle(base, vs[i] - vs[0]);
        }
    }
    bool contains(Point p) const;
};

bool ConvexPolygon::contains(Point p) const {
    ld pa = angle(vs[1] - vs[0], p - vs[0]);
    auto it = upper_bound(angles.begin(), angles.end(), pa);
    if (it == angles.begin()) return false;
    if (it == angles.end()) {
        return Segment{vs[0], *(vs.end()-1)}.contains(p);
    }
    int ind = it - angles.begin();
    return Triangle{vs[0], vs[ind-1], vs[ind]}.contains(p);
}

struct Circle {
    Point o;
    ld r;
    bool contains(Point p) const;
};

bool Circle::contains(Point p) const {
    return distance(p, o) <= r+EPS;
}

bool operator==(Circle c1, Circle c2) {
    return c1.o == c2.o && c1.r == c2.r;
}

pair<pair<Point, Point>, int> operator^(Line l, Circle c) {
    ld rho = distance(c.o, l);
    if (rho > c.r+EPS) {
        return {{c.o, c.o}, 0};
    } else if (abs(rho - c.r) < EPS) {
        return {{c.o + perp(c.o, l), c.o + perp(c.o, l)}, 1};
    } else {
        ld d = sqrt(c.r * c.r - rho * rho);
        Point p = c.o + perp(c.o, l);
        return {{p + l.n * d, p - l.n * d}, 2};
    }
}

pair<pair<Point, Point>, int> operator^(Circle c1, Circle c2) {
    ld rho = distance(c1.o, c2.o);
    if (c1 == c2) {
        return {{c1.o, c1.o}, 3};
    } else if (c1.contains(c2.o)) {
        if (rho - c1.r + c2.r < EPS) {
            return {{c1.o, c1.o}, 0};
        } else if (abs(rho - c1.r + c2.r) < EPS) {
            Point p = c1.o + (c2.o - c1.o).norm() * c1.r;
            return {{p, p}, 1};
        } else {
            ld a = acos((c1.r * c1.r + rho * rho - c2.r * c2.r)/(2 * c1.r * rho));
            Point p = (c2.o - c1.o).norm() * c1.r;
            return {{c1.o + p.rotate(a), c1.o + p.rotate(-a)}, 2};
        }
    } else if (c2.contains(c1.o)) {
        if (rho - c2.r + c1.r < EPS) {
            return {{c2.o, c2.o}, 0};
        } else if (abs(rho - c2.r + c1.r) < EPS) {
            Point p = c2.o + (c1.o - c2.o).norm() * c2.r;
            return {{p, p}, 1};
        } else {
            ld a = acos((c2.r * c2.r + rho * rho - c1.r * c1.r)/(2 * c2.r * rho));
            Point p = (c1.o - c2.o).norm() * c2.r;
            return {{c2.o + p.rotate(a), c2.o + p.rotate(-a)}, 2};
        }
    } else {
        if (c1.r + c2.r - rho < EPS) {
            return {{c1.o, c1.o}, 0};
        } else if (abs(c1.r + c2.r - rho) < EPS) {
            Point p = c1.o + (c2.o - c1.o).norm() * c1.r;
            return {{p, p}, 1};
        } else {
            ld a = acos((c1.r * c1.r + rho * rho - c2.r * c2.r)/(2 * c1.r * rho));
            Point p = (c2.o - c1.o).norm() * c1.r;
            return {{c1.o + p.rotate(a), c1.o + p.rotate(-a)}, 2};
        }
    }
}

pair<pair<Point, Point>, int> tangents(Point p, Circle c) {
    ld rho = distance(p, c.o);
    if (c.contains(p)) {
        if (abs(rho - c.r) < EPS) {
            return {{p, p}, 1};
        } else {
            return {{p, p}, 0};
        }
    } else {
        ld d = sqrt(rho * rho - c.r * c.r);
        return Circle {p, d} ^ c;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    /*freopen("point.in", "r", stdin);
    freopen("point.out", "w", stdout);*/

    cout.setf(ios::fixed);
    cout.precision(10);

    Point o{};
    ld r, a, b, c;
    cin >> o.x >> o.y >> r >> a >> b >> c;
    Circle c1{o, r};
    Line l1{a, b, c};
    auto res = l1 ^ c1;
    //cout << perp(c1.o, l1).x << perp(c1.o, l1).y << '\n';
    cout << res.second << '\n';
    if (res.second == 1) {
        cout << res.first.first.x << ' ' << res.first.first.y << '\n';
    } else if (res.second == 2) {
        cout << res.first.first.x << ' ' << res.first.first.y << '\n';
        cout << res.first.second.x << ' ' << res.first.second.y << '\n';
    }
}