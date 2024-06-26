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
    int x;
    int y;
};

Point operator+(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator*(Point a, int k) {
    return {a.x * k, a.y * k};
}

Point operator*(int k, Point a) {
    return {a.x * k, a.y * k};
}

Point operator/(Point a, int k) {
    return {a.x / k, a.y / k};
}

ll operator*(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

ll operator%(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int sgn(int val) {
    return (0 < val) - (val < 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Point a{}, o{}, b{}, p{};
    cin >> a.x >> a.y >> o.x >> o.y
        >> b.x >> b.y >> p.x >> p.y;

    if (((a - o) % (p - o) == 0 && (a - o) * (p - o) >= 0) || ((b - o) % (p - o) == 0 && (b - o) * (p - o) >= 0)) {
        cout << "YES\n";
        return 0;
    }
    if (sgn((a - o) % (b - o)) == sgn((a - o) % (p - o)) &&
    sgn((b - o) % (a - o)) == sgn((b - o) % (p - o))) {
        cout << "YES\n";
        return 0;
    }
    cout << "NO\n";
}