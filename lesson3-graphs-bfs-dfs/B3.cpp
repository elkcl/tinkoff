#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <set>
#include <functional>

using namespace std;
using ll = long long;
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
    vc used(n, false);
    vector<set<int>> comps;
    function<void(int, int)> dfs = [&g, &used, &dfs, &comps](int v, int comp) -> void {
        used[v] = true;
        comps[comp].insert(v);
        for (auto to : g[v]) {
            if (!used[to]) {
                dfs(to, comp);
            }
        }
    };
    int currComp = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            comps.emplace_back();
            dfs(i, currComp);
            ++currComp;
        }
    }
    cout << comps.size() << "\n";
    for (auto &comp : comps) {
        cout << comp.size() << "\n";
        for (auto v : comp) {
            cout << v + 1 << " ";
        }
        cout << "\n";
    }
}