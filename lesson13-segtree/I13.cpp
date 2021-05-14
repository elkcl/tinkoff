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

const int INF = 1.5e9;
const ll MOD = 1e9 + 7;

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
        t[v] = op(x, t[v]);
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

struct Data {
    int len = 0;
    ll cnt = 0;
};

struct Op {
    constexpr static Data NEUTRAL{0, 0};
    Data operator()(Data a, Data b) {
        if (a.len == b.len)
            return {a.len, (a.cnt + b.cnt) % MOD};
        else if (a.len > b.len)
            return a;
        else
            return b;
    }
};

int main() {
    fast_io

    int n;
    cin >> n;
    vi v(n);
    for (int &el : v)
        cin >> el;
    vi srt(v);
    sort(all(srt));
    auto last = unique(all(srt));
    srt.erase(last, srt.end());
    vi zip(n);
    for (int i = 0; i < n; ++i)
        zip[i] = lower_bound(all(srt), v[i]) - srt.begin();

    vector<Data> dp(srt.size());
    SegTree<Data, Op> seg(dp);
    for (int i = 0; i < n; ++i) {
        int a = zip[i];
        Data pref = seg.get(0, a);
        dp[a] = {pref.len + 1, max(pref.cnt, 1ll)};
        seg.upd(a, {pref.len + 1, max(pref.cnt, 1ll)});
    }
    cout << seg.get(0, srt.size()).cnt << '\n';
}