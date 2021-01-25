#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

struct Oper {
    int type, u, v;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("cutting.in", "r", stdin);
    freopen("cutting.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;
    vvi g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    vector<Oper> op(k);
    for (int i = 0; i < k; ++i) {
        string t;
        int u, v;
        cin >> t >> u >> v;
        if (t == "cut") {
            op[i] = {0, u-1, v-1};
        } else {
            op[i] = {1, u-1, v-1};
        }
    }
    reverse(op.begin(), op.end());

    vi dsu(n);
    iota(dsu.begin(), dsu.end(), 0);
    vi size(n, 1);

    function<int(int)> findSet = [&dsu, &findSet](int v) -> int {
        if (v == dsu[v]) return v;
        return dsu[v] = findSet(dsu[v]);
    };
    auto mergeSets = [&dsu, &size, &findSet](int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            dsu[b] = a;
            size[a] += size[b];
        }
    };

    vi ans;
    for (int i = 0; i < k; ++i) {
        if (op[i].type == 0) {
            mergeSets(op[i].u, op[i].v);
        } else {
            ans.push_back(findSet(op[i].u) == findSet(op[i].v));
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto el : ans) {
        if (el) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}