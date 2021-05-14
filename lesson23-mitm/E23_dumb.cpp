#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif

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
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif



struct point {
    ll x, y;
    int id;
};

ll mind = INT64_MAX;
point ans_a;
point ans_b;

void upd(const point &a, const point &b) {
    ll dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    if (dist < mind) {
        mind = dist;
        ans_a = a;
        ans_b = b;
    }
}

int main() {
    fast_io
    //file_io("rendezvous")

    int n;
    cin >> n;
    vector<point> v(n);
    vector<point> buf(n);
    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        v[i] = {x, y, i};
    }
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            upd(v[i], v[j]);

    cout << ans_a.x << ' ' << ans_a.y << '\n';
    cout << ans_b.x << ' ' << ans_b.y << '\n';
}