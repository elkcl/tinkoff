#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif

#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <numeric>
#include <set>
#include <array>
#include <optional>
#include <cassert>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;
using ull = uint64_t;
using vull = vector<ull>;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

struct SegTree {
    int n;
    vvi t;
    void build(int v, int l, int r, const vi &a);
    ll get_lb(int ql, int qr, int x, int v = 1, int vl = 0, int vr = -1) const;
    ll get_ub(int ql, int qr, int x, int v = 1, int vl = 0, int vr = -1) const;
    ll get_betw(int ql, int qr, int xl, int xr, int v = 1, int vl = 0, int vr = -1) const;
    explicit SegTree(const vi &a) {
        n = a.size();
        t.resize(4 * n);
        build(1, 0, n, a);
    }
};

void SegTree::build(int v, int l, int r, const vi &a) {
    if (l + 1 == r) {
        t[v].push_back(a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, a);
    build(2 * v + 1, m, r, a);
    t[v].resize(t[2 * v].size() + t[2 * v + 1].size());
    merge(all(t[2 * v]), all(t[2 * v + 1]), t[v].begin());
}

ll SegTree::get_lb(int ql, int qr, int x, int v, int vl, int vr) const {
    if (vr == -1)
        vr = n;
    if (ql >= vr || qr <= vl) {
        return 0;
    }
    if (ql <= vl && qr >= vr) {
        return lower_bound(all(t[v]), x) - t[v].begin();
    }
    int m = (vl + vr) / 2;
    return get_lb(ql, qr, x, 2 * v, vl, m) + get_lb(ql, qr, x, 2 * v + 1, m, vr);
}

ll SegTree::get_ub(int ql, int qr, int x, int v, int vl, int vr) const {
    if (vr == -1)
        vr = n;
    if (ql >= vr || qr <= vl) {
        return 0;
    }
    if (ql <= vl && qr >= vr) {
        return t[v].size() - (upper_bound(all(t[v]), x) - t[v].begin());
    }
    int m = (vl + vr) / 2;
    return get_ub(ql, qr, x, 2 * v, vl, m) + get_ub(ql, qr, x, 2 * v + 1, m, vr);
}

ll SegTree::get_betw(int ql, int qr, int xl, int xr, int v, int vl, int vr) const {
    return qr - ql - get_lb(ql, qr, xl, v, vl, vr) - get_ub(ql, qr, xr, v, vl, vr);
}

int main() {
    fast_io

    int n, m;
    cin >> n >> m;
    vi v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    SegTree seg(v);
    for (int q = 0; q < m; ++q) {
        int ql, qr, xl, xr;
        cin >> ql >> qr >> xl >> xr;
        --ql;
        cout << seg.get_betw(ql, qr, xl, xr) << '\n';
    }
}