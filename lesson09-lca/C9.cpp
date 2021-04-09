#pragma GCC optimize("O3")

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
using vvii = vector<vii>;
using vc = vector<char>;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    /*freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);*/

    int n;
    cin >> n;
    vll vx(n);
    for (int i = 0; i < n; ++i) {
        cin >> vx[i];
    }
    vvi g(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }

    vii h;
    vll pref(n);
    vc used(n, false);
    vi first(n, -1);
    auto dfs = [&g, &h, &used, &pref, &vx](int v) -> void{
        auto dfs_in = [&](int v, int currh, ll currs, const auto &fun) -> void {
            h.push_back({currh, v});
            used[v] = true;
            pref[v] = currs + vx[v];
            for (int to : g[v]) {
                if (!used[to]) {
                    fun(to, currh+1, pref[v], fun);
                    h.push_back({currh, v});
                }
            }
            //h.push_back({currh, vx});
        };
        dfs_in(v, 0, 0, dfs_in);
    };

    dfs(0);
    int s = h.size();
    for (int i = 0; i < s; ++i) {
        if (first[h[i].second] == -1) first[h[i].second] = i;
    }


    vi logs(s+1, 0);
    logs[1] = 0;
    for (int i = 2; i < s+1; ++i) {
        logs[i] = logs[i / 2] + 1;
    }
    vi tp(logs[s]+1);
    tp[0] = 1;
    for (int i = 1; i < logs[s]+1; ++i) {
        tp[i] = 2 * tp[i-1];
    }
    vvii st(s, vii(logs[s]+1));
    for (int i = 0; i < s; ++i) {
        st[i][0] = h[i];
    }
    for (int j = 1; j < logs[s]+1; ++j) {
        for (int i = 0; i < s - tp[j] + 1; ++i) {
            st[i][j] = min(st[i][j - 1], st[i + tp[j - 1]][j - 1]);
        }
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int v1, v2;
        cin >> v1 >> v2;
        --v1;
        --v2;
        if (first[v1] > first[v2]) swap(v1, v2);
        int k = logs[first[v2] - first[v1] + 1];
        ii lca = min(st[first[v1]][k], st[first[v2] - tp[k] + 1][k]);
        cout << pref[v1] + pref[v2] - 2*pref[lca.second] + vx[lca.second] << '\n';
    }
}

