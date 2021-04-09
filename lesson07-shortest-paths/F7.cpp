#pragma GCC optimize("O3")

// resend (3)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>

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
    freopen("dijkstra.in", "r", stdin);
    freopen("dijkstra.out", "w", stdout);

    int n, s, f;
    cin >> n >> s >> f;
    --s;
    --f;
    vvi g(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }

    vi dist(n, INF);
    vc used(n, false);
    dist[s] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || dist[j] < dist[v]))
                v = j;
        }
        if (dist[v] == INF)
            break;
        used[v] = true;
        for (int to = 0; to < n; ++to) {
            if (g[v][to] != -1)
                dist[to] = min(dist[to], dist[v] + g[v][to]);
        }
    }

    if (dist[f] == INF) {
        cout << "-1\n";
    } else {
        cout << dist[f] << '\n';
    }
}

