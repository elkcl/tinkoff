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
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vll v(n+1, 0);
    fenwick<ll> f(n);
    for (int q = 0; q < k; ++q) {
        char t;
        cin >> t;
        if (t == 'A') {
            int i;
            ll x;
            cin >> i >> x;
            f.upd(i, x - v[i]);
            v[i] = x;
        } else if (t == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << f.sum(l, r) << '\n';
        }
    }
}