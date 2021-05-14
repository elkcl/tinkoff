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

template<typename T>
struct fenwick {
    int size;
    vector<T> f;

    explicit fenwick(int n): size{n} {
        f.resize(n+1, 0);
    }

    T sum(int k) {
        T ans = 0;
        for (int i = k; i > 0; i -= i & -i)
            ans += f[i];
        return ans;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l-1);
    }

    void upd(int k, T x) {
        for (int i = k; i <= size; i += i & -i)
            f[i] += x;
    }

    int find_last_less(int x) {
        int k = 0;
        for (int i = static_cast<int>(log2(size)); i >= 0; --i) {
            if (k + (1 << i) <= size && f[k + (1 << i)] < x) {
                k += (1 << i);
                x -= f[k];
            }
        }
        return k;
    }
};

int main() {
    fast_io
    file_io("kthzero")

    int n, m;
    cin >> n;
    fenwick<int> fen(n);
    vi v(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        v[i + 1] = a == 0;
        fen.upd(i + 1, a == 0);
    }
    cin >> m;
    for (int q = 0; q < m; ++q) {
        char t;
        cin >> t;
        if (t == 'u') {
            int i, x;
            cin >> i >> x;
            fen.upd(i, (x == 0) - v[i]);
            v[i] = x == 0;
        } else if (t == 's') {
            int l, r, k;
            cin >> l >> r >> k;
            k += fen.sum(0, l - 1);
            int x = fen.find_last_less(k);
            if (x == n || x >= r)
                cout << "-1\n";
            else
                cout << x + 1 << '\n';
        }
    }
}