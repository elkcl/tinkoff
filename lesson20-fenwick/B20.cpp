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

    int n, m;
    cin >> n >> m;
    fenwick<ll> f(n+1);
    for (int q = 0; q < m; ++q) {
        char t;
        cin >> t;
        if (t == '+') {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            f.upd(l, x);
            f.upd(r+1, -x);
        } else if (t == '?') {
            int k;
            cin >> k;
            cout << f.sum(1, k) << '\n';
        }
    }
}