#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    vi v1(n);
    for (int i = 0; i < n; ++i) {
        cin >> v1[i];
    }
    cin >> m;
    vi v2(m);
    for (int i = 0; i < m; ++i) {
        cin >> v2[i];
    }
    vvi dp(n+1, vi(m+1));
    for (int i = 0; i < n+1; ++i) {
        dp[i][0] = 0;
    }
    for (int i = 1; i < m+1; ++i) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (v1[i-1] == v2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    cout << dp[n][m] << "\n";
}