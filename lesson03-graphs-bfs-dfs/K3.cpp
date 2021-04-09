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
    }

    vc used(n, 0);
    function<bool(int)> dfs = [&g, &used, &dfs](int v) {
        used[v] = 1;
        for (auto to : g[v]) {
            if (used[to] == 0) {
                if (dfs(to)) return true;
            } else if (used[to] == 1) {
                return true;
            }
        }
        used[v] = 2;
        return false;
    };

    for (int i = 0; i < n; ++i) {
        if (used[i] == 0) {
            if (dfs(i)) {
                cout << "1\n";
                return 0;
            }
        }
    }
    cout << "0\n";
}