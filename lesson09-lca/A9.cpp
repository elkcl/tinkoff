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

    int n;
    cin >> n;
    vvi g(n);

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

}