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
#include <cassert>

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

bool kuhn(vvi &g, vc &used, vi &ps, int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (ps[to] == -1 || kuhn(g, used, ps, ps[to])) {
            ps[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    fast_io

    int n, m;
    cin >> n >> m;
    vvi g(n);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        while (a != 0) {
            g[i].push_back(a - 1);
            cin >> a;
        }
    }

    vi ps(m, -1);
    vc used(n, false);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += kuhn(g, used, ps, i);
        fill(all(used), false);
    }

    cout << ans << '\n';
    for (int i = 0; i < m; ++i) {
        if (ps[i] != -1)
            cout << ps[i] + 1 << ' ' << i + 1 << '\n';
    }
}