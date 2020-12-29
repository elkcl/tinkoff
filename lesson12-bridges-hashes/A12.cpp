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
    vvi gt(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
        gt[b-1].push_back(a-1);
    }

    vi comps(n);
    int compCounter = 1;
    vc used(n, false);
    vi toutOrder;
    function<void(int)> dfs1 = [&g, &used, &toutOrder, &dfs1](int v) {
        used[v] = true;
        for (auto to : g[v]) {
            if (!used[to]) {
                dfs1(to);
            }
        }
        toutOrder.push_back(v);
    };
    function<void(int)> dfs2 = [&gt, &used, &comps, &compCounter, &dfs2](int v) {
        used[v] = true;
        comps[v] = compCounter;
        for (auto to : gt[v]) {
            if (!used[to]) {
                dfs2(to);
            }
        }
    };

    for (int i = 0; i < n; ++i) {
        if (!used[i]) dfs1(i);
    }
    fill(used.begin(), used.end(), false);

    for (int i = 0; i < n; ++i) {
        int v = toutOrder[n-1 - i];
        if (!used[v]) {
            dfs2(v);
            ++compCounter;
        }
    }

    cout << compCounter-1 << '\n';
    for (int i = 0; i < n; ++i) {
        cout << comps[i] << ' ';
    }
    cout << '\n';
}