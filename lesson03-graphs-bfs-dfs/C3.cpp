#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vc = vector<char>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;
    vvi g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a != t && b != t) {
            g[a - 1].push_back(b - 1);
            g[b - 1].push_back(a - 1);
        }
    }
    vi used(n, 0);
    function<void(int, int)> dfs = [&g, &used, &dfs](int v, int comp) -> void {
        used[v] = comp;
        for (auto to : g[v]) {
            if (used[to] == 0) {
                dfs(to, comp);
            }
        }
    };
    int lastComp = 1;
    int k;
    cin >> k;
    for (int q = 0; q < k; ++q) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (used[a] == 0) {
            if (used[b] == 0) {
                dfs(a, lastComp);
                ++lastComp;
                if (used[b] == 0) {
                    cout << "No\n";
                } else {
                    cout << "Yes\n";
                }
            } else {
                cout << "No\n";
            }
        } else {
            if (used[b] == 0) {
                cout << "No\n";
            } else {
                if (used[a] == used[b]) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
            }
        }
    }
}