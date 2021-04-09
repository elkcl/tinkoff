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

    int n, s;
    cin >> n >> s;
    --s;
    vvi m(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }

    vc used(n, false);
    function<void(int)> dfs = [n, &m, &used, &dfs](int v) {
        used[v] = true;
        for (int to = 0; to < n; ++to) {
            if (!used[to] && m[v][to]) dfs(to);
        }
    };

    dfs(s);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (used[i]) ++ans;
    }
    cout << ans << '\n';
}