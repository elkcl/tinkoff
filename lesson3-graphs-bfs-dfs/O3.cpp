#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <deque>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vc = vector<char>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    int s = (x1 - 1)*n + y1-1;
    int f = (x2 - 1)*n + y2-1;
    vvi g(n*n);
    auto add = [n, &g](int x1, int y1, int x2, int y2) {
        if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < n) {
            g[x1 * n + y1].push_back(x2 * n + y2);
        }
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            add(i, j, i+2, j+1);
            add(i, j, i+2, j-1);
            add(i, j, i-2, j+1);
            add(i, j, i-2, j-1);
            add(i, j, i+1, j+2);
            add(i, j, i+1, j-2);
            add(i, j, i-1, j+2);
            add(i, j, i-1, j-2);
        }
    }

    vi dist(n*n, n*n);
    dist[s] = 0;
    deque<int> q;
    vi p(n*n);
    q.push_back(s);
    p[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int to : g[v]) {
            if (dist[to] > dist[v] + 1) {
                dist[to] = dist[v] + 1;
                q.push_back(to);
                p[to] = v;
            }
        }
    }

    cout << dist[f] << '\n';
    vi path;
    for (int v = f; v != -1; v = p[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    for (auto i : path) {
        cout << i / n + 1 << ' ' << i % n + 1 << '\n';
    }
}