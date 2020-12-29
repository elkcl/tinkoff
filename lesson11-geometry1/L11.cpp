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

    int n;
    cin >> n;
    vector<Point> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].x >> v[i].y;
    }

    ll sum = v[n-1] % v[0];
    for (int i = 0; i < n-1; ++i) {
        sum += v[i] % v[i+1];
    }

    sum = abs(sum);
    if (sum % 2 == 0) {
        cout << sum / 2 << '\n';
    } else {
        cout << sum / 2 << ".5\n";
    }
}