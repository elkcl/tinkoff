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
using vvii = vector<vii>;
using vc = vector<char>;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    freopen("path.in", "r", stdin);
//    freopen("path.out", "w", stdout);

    int n;
    cin >> n;
    vvi dist(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
            if (dist[i][j] == -1)
                dist[i][j] = INF;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] != INF)
                ans = max(ans, dist[i][j]);
        }
    }

    cout << ans << '\n';
}

