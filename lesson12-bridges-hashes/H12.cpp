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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vvi g(n);
    for (int i = 0; i < m; ++i) {
        int b, e;
        cin >> b >> e;
        g[b-1].push_back(e-1);
        g[e-1].push_back(b-1);
    }

    vc used(n, false);
    vi tin(n);
    vc ans(n, false);
    vi d(n);
    int timer = 0;
    auto dfs = [&g, &used, &d, &tin, &ans, &timer](int v) -> void {
        auto dfs_in = [&](int v, int p, const auto &fun) -> void {
            used[v] = true;
            d[v] = tin[v] = timer++;
            int childCount = 0;
            for (int to : g[v]) {
                if (to == p) continue;
                if (used[to]) {
                    d[v] = min(d[v], tin[to]);
                } else {
                    fun(to, v, fun);
                    d[v] = min(d[v], d[to]);
                    if (d[to] >= tin[v] && p != -1) {
                        ans[v] = true;
                    }
                    ++childCount;
                }
            }
            if (p == -1 && childCount > 1) {
                ans[v] = true;
            }
        };
        dfs_in(v, -1, dfs_in);
    };
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    cout << count(ans.begin(), ans.end(), true) << '\n';
    for (int i = 0; i < n; ++i) {
        if (ans[i]) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
}