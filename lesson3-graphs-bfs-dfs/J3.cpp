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
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }

    vc used(n, false);
    bool tree = true;
    function<void(int, int)> dfs = [&g, &used, &tree, &dfs](int v, int p) {
        used[v] = true;
        for (auto to : g[v]) {
            if (to == p) continue;
            if (used[to]) {
                tree = false;
                return;
            }
            dfs(to, v);
        }
    };

    dfs(0, -1);
    if (!tree) {
        cout << "NO\n";
    } else {
        bool connected = true;
        for (auto v : used) {
            if (!v) {
                connected = false;
                break;
            }
        }
        if (connected) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}