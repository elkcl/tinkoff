#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vvi was(n, vi(m, -1));
    was[0][0] = 1;
    function<ll(int, int)> ans = [&was, &ans, n, m](int i, int j) -> ll {
        if (i < 0 || i >= n || j < 0 || j >= m) return 0;
        if (was[i][j] != -1) return was[i][j];

        return was[i][j] = ans(i-2, j-1)
                         + ans(i-2, j+1)
                         + ans(i-1, j-2)
                         + ans(i+1, j-2);
    };
    cout << ans(n-1, m-1) << "\n";
}