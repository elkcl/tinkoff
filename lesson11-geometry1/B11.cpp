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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(ios::fixed);
    cout.precision(2);

    Point a{};
    Point b{};
    Point c{};
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    cout << abs(static_cast<double>((b-a) % (c-a)) / 2) << '\n';
}