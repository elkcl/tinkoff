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

template<typename T, typename F>
struct SegTree {
    int n;
    vector<T> t;
    vi left;
    vi right;
    F op{};
    void build(int v, int l, int r, const vector<T> &a);
    void upd(int v, int pos, T x);
    T get(int v, int ql, int qr);
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
T SegTree<T, F>::get(int v, int ql, int qr) {
    if (ql >= right[v] || qr <= left[v]) {
        return F::NEUTRAL;
    }
    if (ql <= left[v] && qr >= right[v]) {
        return t[v];
    }
    return op(get(2 * v, ql, qr), get(2 * v + 1, ql, qr));
}

template<typename T, typename F>
void SegTree<T, F>::upd(int v, int pos, T x) {
    if (left[v] + 1 == right[v]) {
        t[v] = x;
        return;
    }
    int m = (left[v] + right[v]) / 2;
    if (pos < m) {
        upd(2 * v, pos, x);
    } else {
        upd(2 * v + 1, pos, x);
    }
    t[v] = op(t[2 * v], t[2 * v + 1]);
}

struct MaxII {
    ii operator()(ii a, ii b) {
        return max(a, b);
    }
    constexpr static const ii NEUTRAL {0, -1};
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("index-max.in", "r", stdin);
    freopen("index-max.out", "w", stdout);

    int n, k;
    cin >> n;
    vii v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first;
        v[i].second = i;
    }
    cin >> k;
    SegTree<ii, MaxII> st{v};

    for (int q = 0; q < k; ++q) {
        int a, b;
        cin >> a >> b;
        cout << st.get(1, a-1, b).second+1 << '\n';
    }
}