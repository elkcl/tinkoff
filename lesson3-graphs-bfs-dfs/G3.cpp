#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <deque>
#include <utility>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
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
        g[b-1].push_back(a-1);
    }

    vc red(n);
    vc used(n, false);
    deque<int> q;
    auto bfs = [&red, &used, &g, &q](int s) {
        red[s] = true;
        used[s] = true;
        q.push_back(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int to : g[v]) {
                if (!used[to]) {
                    used[to] = true;
                    red[to] = !red[v];
                    q.push_back(to);
                } else {
                    if (red[to] == red[v]) {
                        return -1;
                    }
                }
            }
        }
        return 0;
    };
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            int res = bfs(i);
            if (res == -1) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
}