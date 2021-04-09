#pragma GCC optimize("O3")

// resend (3)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <deque>
#include <tuple>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vll = vector<ll>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen("path.in", "r", stdin);
    //freopen("path.out", "w", stdout);

    int n, m, k, s, f;
    cin >> n >> m >> k >> s >> f;
    --s;
    --f;
    vector<tuple<int, int, int>> g;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g.emplace_back(a-1, b-1, w);
    }

    vvi dist(k+1, vi(n, INF));
    dist[0][s] = 0;
    for (int i = 1; i < k+1; ++i) {
        for (auto&& [from, to, w] : g) {
            if (dist[i-1][from] != INF)
                dist[i][to] = min(dist[i][to], dist[i-1][from] + w);
        }
    }

    int ans = INF;
    for (int i = 0; i < k+1; ++i) {
        ans = min(ans, dist[i][f]);
    }
    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}

