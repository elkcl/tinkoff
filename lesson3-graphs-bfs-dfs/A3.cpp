#pragma GCC optimize("O3")

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vc = vector<char>;
using vvc = vector<vc>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vvc g(n, vc(n, false));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a-1][b-1] = true;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << static_cast<bool>(g[i][j]) << " ";
        }
        cout << "\n";
    }
}