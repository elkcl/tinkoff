#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif
#pragma GCC optimize("O3")
#pragma GCC target("avx2")

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

template<typename T, typename F>
struct SegTree {
    ull n;
    vector<T> t;
    vull &left;
    vull &right;
    F op{};
    void build(ull v, ull l, ull r, const vector<T> &a);
    void upd(ull pos, T x, ull v = 1);
    T get(ull ql, ull qr, ull v = 1);
    int kth(ll k, ull v = 1);
    explicit SegTree(const vector<T> &a, vull &l, vull &r): left{l}, right{r} {
        n = a.size();
        t.resize(4 * n);
        build(1, 0, n, a);
    }
};

template<typename T, typename F>
void SegTree<T, F>::build(ull v, ull l, ull r, const vector<T> &a) {
    left[v] = l;
    right[v] = r;
    if (l + 1 == r) {
        t[v] = a[l];
        return;
    }
    ull m = (l + r) / 2;
    build(2 * v, l, m, a);
    build(2 * v + 1, m, r, a);
    t[v] = op(t[2 * v], t[2 * v + 1]);
}

template<typename T, typename F>
T SegTree<T, F>::get(ull ql, ull qr, ull v) {
    if (ql >= right[v] || qr <= left[v]) {
        return F::NEUTRAL;
    }
    if (ql <= left[v] && qr >= right[v]) {
        return t[v];
    }
    return op(get(ql, qr, 2 * v), get(ql, qr, 2 * v + 1));
}

template<typename T, typename F>
void SegTree<T, F>::upd(ull pos, T x, ull v) {
    if (left[v] + 1 == right[v]) {
        t[v] = x;
        return;
    }
    ull m = (left[v] + right[v]) / 2;
    if (pos < m) {
        upd(pos, x, 2 * v);
    } else {
        upd(pos, x, 2 * v + 1);
    }
    t[v] = op(t[2 * v], t[2 * v + 1]);
}

template<typename T, typename F>
int SegTree<T, F>::kth(ll k, ull v) {
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

template<typename T>
struct Add {
    static const T NEUTRAL = 0;
    T operator()(T a, T b) const {
        return a + b;
    }
};

int main() {
    fast_io
    //file_io("kthzero")
    freopen("/home/elk/Development/aa.txt", "r", stdin);
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
    vi dp(srt.size(), 0);
    vull left(4 * srt.size());
    vull right(4 * srt.size());
    SegTree<int, Add<int>> seg0(dp, left, right);
    SegTree<int, Add<int>> seg1(dp, left, right);
    SegTree<int, Add<int>> seg2(dp, left, right);
    for (int i = 0; i < n; ++i) {
        int a = zip[i];
        seg0.upd(a, dp[a] + 1);
        ++dp[a];
        seg1.upd(a, seg0.get(a + 1, srt.size()));
        seg2.upd(a, seg1.get(a + 1, srt.size()));
    }
    cout << seg2.get(0, srt.size()) << '\n';
}