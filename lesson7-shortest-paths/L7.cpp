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

    int n;
    cin >> n;
    vector<tuple<int, int, int>> g;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            cin >> w;
            g.emplace_back(i, j, w);
        }
    }

    vi dist(n, INF);
    vi p(n, -1);
    dist[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (auto&& [from, to, w] : g) {
            if (dist[from] != INF)
                dist[to] = min(dist[to], dist[from] + w);
        }
    }


}

