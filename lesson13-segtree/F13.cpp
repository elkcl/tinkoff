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
    T get(int ql, int qr, int v = 1) const;
    void getArr(int ql, int qr, vi &vec, int v = 1) const;
    int kth(T k, int v = 1) const;
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
T SegTree<T, F>::get(int ql, int qr, int v) const {
    if (ql >= right[v] || qr <= left[v]) {
        return F::NEUTRAL;
    }
    if (ql <= left[v] && qr >= right[v]) {
        return t[v];
    }
    return op(get(ql, qr, 2 * v), get(ql, qr, 2 * v + 1));
}

template<typename T, typename F>
void SegTree<T, F>::getArr(int ql, int qr, vi &vec, int v) const {
    if (ql >= right[v] || qr <= left[v]) {
        return;
    }
    if (ql <= left[v] && qr >= right[v]) {
        vec.push_back(v);
        return;
    }
    getArr(ql, qr, vec, 2 * v);
    getArr(ql, qr, vec, 2 * v + 1);
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
int SegTree<T, F>::kth(T k, int v) const {
    if (left[v] + 1 == right[v])
        return left[v];
    if (t[v * 2] >= k)
        return kth(k, v * 2);
    else
        return kth(k, v * 2 + 1);
}

struct Max {
    static const int NEUTRAL = 0;
    int operator()(int a, int b) const {
        return max(a, b);
    }
};

int main() {
    fast_io
    file_io("nearandmore")

    int n, m;
    cin >> n >> m;
    vi vin(n);
    for (int &el : vin)
        cin >> el;
    SegTree<int, Max> seg(vin);

    for (int q = 0; q < m; ++q) {
        int t, i, x;
        cin >> t >> i >> x;
        --i;
        if (t == 0) {
            seg.upd(i, x);
        } else if (t == 1) {
            vi vec;
            seg.getArr(i, n, vec);
            int v = -1;
            for (int el : vec) {
                if (seg.t[el] >= x) {
                    v = el;
                    break;
                }
            }
            if (v == -1) {
                cout << "-1\n";
                continue;
            }
            cout << seg.kth(x, v) + 1 << '\n';
        }
    }
}