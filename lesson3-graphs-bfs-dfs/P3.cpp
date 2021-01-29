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

    int n;
    cin >> n;
    vvi g(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }

    vc used(n, false);
    auto bfs2 = [n, &g, &used](int s) -> ii {
        vi dist(n, n);
        deque<int> q;
        dist[s] = 0;
        q.push_back(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            used[v] = true;
            for (int to : g[v]) {
                if (dist[to] > dist[v] + 1) {
                    dist[to] = dist[v] + 1;
                    q.push_back(to);
                }
            }
        }
        int ind = s;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[i] != n && dist[i] > ans) {
                ind = i;
                ans = dist[i];
            }
        }
        fill(dist.begin(), dist.end(), n);
        dist[ind] = 0;
        q.push_back(ind);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            used[v] = true;
            for (int to : g[v]) {
                if (dist[to] > dist[v] + 1) {
                    dist[to] = dist[v] + 1;
                    q.push_back(to);
                }
            }
        }
        ans = 0;
        for (int i = 0; i < n; ++i) {
            if (dist[i] != n && dist[i] > ans) {
                ind = i;
                ans = dist[i];
            }
        }
        return {ind, ans};
    };
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            ans = max(ans, bfs2(i).second);
        }
    }
    cout << ans+1 << '\n';
}