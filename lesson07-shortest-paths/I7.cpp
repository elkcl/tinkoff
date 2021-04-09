#pragma GCC optimize("O3")

// resend (3)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <deque>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vll = vector<ll>;
using vi = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
using vc = vector<char>;

const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);

    int n, m, s;
    cin >> n >> m >> s;
    --s;
    vvi dist(n, vi(n, INF));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        ll a, b, w;
        cin >> a >> b >> w;
        dist[a-1][b-1] = min(w, dist[a-1][b-1]);
    }



    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], max(dist[i][k] + dist[k][j], -INF));
                }
            }
        }
    }

    for (int u = 0; u < n; ++u) {
        if (dist[s][u] == INF) {
            cout << "*\n";
            continue;
        }
        bool ret = true;
        for (int t = 0; t < n; ++t) {
            if (dist[s][t] != INF && dist[t][t] < 0 && dist[t][u] != INF) {
                cout << "-\n";
                ret = false;
                break;
            }
        }
        if (ret)
            cout << dist[s][u] << '\n';
    }
}

