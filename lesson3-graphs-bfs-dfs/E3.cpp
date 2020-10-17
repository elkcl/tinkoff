#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <string>

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
    vvi g1(n);
    vvi g2(n);
    for (int i = 0; i < n - 1; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n - i; ++j) {
            if (s[j] == 'R') {
                g1[i].push_back(i+j+1);
            } else if (s[j] == 'B') {
                g2[i].push_back(i+j+1);
            }
        }
    }

    function<void(int, vvi&, vi&)> dfs = [&dfs](int v, vvi &g, vi &used) -> void {
        used[v] = true;
        for (auto to : g[v]) {
            if (!used[to]) {
                dfs(to, g, used);
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        vi used1(n, false);
        vi used2(n, false);
        dfs(i, g1, used1);
        dfs(i, g2, used2);
        bool conf = false;
        for (int j = i+1; j < n; ++j) {
            if (used1[j] && used2[j]) {
                conf = true;
                break;
            }
        }
        if (conf) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
}