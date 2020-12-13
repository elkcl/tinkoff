#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <functional>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vc = vector<char>;

struct vertex {
    int w;
    vi n;
};

using graph = vector<vertex>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int l = static_cast<int>(ceil(log2(n)));
    graph g(n);
    for (int i = 0; i < n; ++i) {
        cin >> g[i].w;
    }
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a-1].n.push_back(b-1);
        g[b-1].n.push_back(a-1);
    }
    int m;
    cin >> m;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> randRoot(0, n-1);
    //int root = randRoot(mt);
    int root = 0;

    vi s(n);
    s[root] = g[root].w;
    vi tin(n);
    vi tout(n);
    vvi up(n, vi(l+1));
    int timer = 0;
    function<void(int, int)> dfs = [&dfs, &g, &s, &tin, &tout, &up, &timer, l](int v, int p) {
        tin[v] = timer++;
        up[v][0] = p;
        for (int i = 1; i < l+1; ++i) {
            up[v][i] = up[up[v][i-1]][i-1];
        }
        for (auto to : g[v].n) {
            if (to != p) {
                s[to] = s[v] + g[to].w;
                dfs(to, v);
            }
        }
        tout[v] = timer++;
    };
    dfs(root, root);

    auto upper = [&tin, &tout](int a, int b) {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    };

    for (int q = 0; q < m; ++q) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        int lca;
        if (upper(a, b)) {
            lca = a;
        } else if (upper(b, a)) {
            lca = b;
        } else {
            for (int i = l; i >= 0; --i) {
                if (!upper(up[a][i], b)) a = up[a][i];
            }
            lca = up[a][0];
        }
        cout << s[a] + s[b] - 2 * s[lca] + g[lca].w << '\n';
    }
}