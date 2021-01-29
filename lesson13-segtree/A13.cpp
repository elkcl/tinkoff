#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>

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

struct Seq {
    int n;
    int len;
    int lenL;
    int lenR;
    bool neutral;
};

struct opSeq {
    constexpr static const Seq NEUTRAL{0, 0, 0, 0, true};
    Seq operator()(Seq a, Seq b) {
        if (a.neutral) {
            return b;
        } else if (b.neutral) {
            return a;
        } else {
            Seq c{};
            c.n = a.n + b.n;
            if (a.lenL == a.n) {
                c.lenL = a.lenL + b.lenL;
            } else {
                c.lenL = a.lenL;
            }
            if (b.lenR == b.n) {
                c.lenR = b.lenR + a.lenR;
            } else {
                c.lenR = b.lenR;
            }
            c.len = max(a.lenR + b.lenL, max(a.len, b.len));
            return c;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    /*freopen("index-max.in", "r", stdin);
    freopen("index-max.out", "w", stdout);*/

    int n, m;
    cin >> n;
    vector<Seq> vs(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x == 0) {
            vs[i] = {1, 1, 1, 1, false};
        } else {
            vs[i] = {1, 0, 0, 0, false};
        }
    }
    SegTree<Seq, opSeq> st(vs);
    cin >> m;

    for (int q = 0; q < m; ++q) {
        string type;
        cin >> type;
        if (type == "UPDATE") {
            int i, x;
            cin >> i >> x;
            --i;
            if (x == 0) {
                st.upd(1, i, {1, 1, 1, 1, false});
            } else {
                st.upd(1, i, {1, 0, 0, 0, false});
            }
        } else if (type == "QUERY") {
            int l, r;
            cin >> l >> r;
            cout << st.get(1, l-1, r).len << '\n';
        }
    }
}