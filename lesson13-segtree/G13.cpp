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

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

template<typename T, typename F>
struct SegTree {
    int n;
    vector<T> t;
    vi left;
    vi right;
    F op{};
    void build(int v, int l, int r, const vector<T> &a);
    void upd(int pos, T x, int v = 1);
    T get(int ql, int qr, int v = 1);
    int kth(ll k, int v = 1);
    explicit SegTree(const vector<T> &a) {
        n = a.size();
        t.resize(4 * n);
        left.resize(4 * n);
        right.resize(4 * n);
        build(1, 0, n, a);
    }
};

template<typename T, typename F>
void SegTree<T, F>::build(int v, int l, int r, const vector<T> &a) {
    left[v] = l;
    right[v] = r;
    if (l + 1 == r) {
        t[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, a);
    build(2 * v + 1, m, r, a);
    t[v] = op(t[2 * v], t[2 * v + 1]);
}

template<typename T, typename F>
T SegTree<T, F>::get(int ql, int qr, int v) {
    if (ql >= right[v] || qr <= left[v]) {
        return F::NEUTRAL;
    }
    if (ql <= left[v] && qr >= right[v]) {
        return t[v];
    }
    return op(get(ql, qr, 2 * v), get(ql, qr, 2 * v + 1));
}

template<typename T, typename F>
void SegTree<T, F>::upd(int pos, T x, int v) {
    if (left[v] + 1 == right[v]) {
        t[v] = x;
        return;
    }
    int m = (left[v] + right[v]) / 2;
    if (pos < m) {
        upd(pos, x, 2 * v);
    } else {
        upd(pos, x, 2 * v + 1);
    }
    t[v] = op(t[2 * v], t[2 * v + 1]);
}

template<typename T, typename F>
int SegTree<T, F>::kth(ll k, int v) {
    if (k >= t[v])
        return -1;
    if (k < 0)
        return -1;
    if (left[v] + 1 == right[v])
        return left[v];
    if (t[v * 2] > k)
        return kth(k, v * 2);
    else
        return kth(k - t[v * 2], v * 2 + 1);
}

struct Add {
    static const ll NEUTRAL = 0;
    ll operator()(ll a, ll b) {
        return a + b;
    }
};

int main() {
    fast_io
    file_io("kthzero")

    int n, m;
    cin >> n;
    vll v(n);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if (a == 0)
            v[i] = 1;
        else
            v[i] = 0;
    }
    cin >> m;
    SegTree<ll, Add> seg(v);

    for (int q = 0; q < m; ++q) {
        char t;
        cin >> t;
        if (t == 's') {
            int l, r;
            ll k;
            cin >> l >> r >> k;
            --l;
            --r;
            --k;
            k += seg.get(0, l);
            int x = seg.kth(k);
            if (x == -1 || x > r)
                cout << "-1\n";
            else
                cout << x + 1 << '\n';
        } else if (t == 'u') {
            int i;
            ll x;
            cin >> i >> x;
            seg.upd(i - 1, x == 0);
        }
    }
}