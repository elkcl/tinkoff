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
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("kefir.in", "r", stdin);
    freopen("kefir.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    vvi g(n);
    int f = n-1;
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u;
        --v;
        if (c == 1) {
            g[u].push_back(v);
            g[v].push_back(u);
        } else {
            g.emplace_back();
            g[u].push_back(n);
            g[v].push_back(n);
            g[n].push_back(u);
            g[n].push_back(v);
            ++n;
        }
    }

    deque<int> q;
    q.push_back(0);
    vi dist(n, n);
    dist[0] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int to : g[v]) {
            if (dist[to] > dist[v] + 1) {
                dist[to] = dist[v] + 1;
                q.push_back(to);
            }
        }
    }

    if (dist[f] == n) {
        cout << "-1\n";
    } else {
        cout << dist[f] << '\n';
    }
}

