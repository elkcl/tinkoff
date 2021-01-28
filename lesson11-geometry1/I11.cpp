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

struct Point {
    ld x;
    ld y;
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

ll sgn(ld val) {
    return (0 < val) - (val < 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].x >> v[i].y;
    }

    ll s = sgn((v[1] - v[0]) % (v[2] - v[0]));
    for (int i = 1; i < n-2; ++i) {
        if (sgn((v[i+1] - v[i]) % (v[i+2] - v[i])) != s) {
            cout << "NO\n";
            return 0;
        }
    }
    if (sgn((v[n-1] - v[n-2]) % (v[0] - v[n-2])) != s) {
        cout << "NO\n";
        return 0;
    }
    if (sgn((v[0] - v[n-1]) % (v[1] - v[n-1])) != s) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
}