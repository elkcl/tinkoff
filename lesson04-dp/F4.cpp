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

    int n;
    cin >> n;
    vi v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    vvi dp(n, vi(n));
    for (int i = 1; i < n-1; ++i) {
        dp[i][i+1] = v[i+1] - v[i];
        dp[i][i] = min(v[i] - v[i - 1], v[i + 1] - v[i]);
        for (int j = i-1; j >= 0; --j) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = dp[0][1] = v[1] - v[0];
    dp[n-1][n-1] = v[n-1] - v[n-2];
    for (int j = n-2; j >= 0; --j) {
        dp[n-1][j] = 0;
    }

    for (int l = n-3; l >= 0; --l) {
        for (int r = l+2; r < n; ++r) {
            if (r - l == 2) {
                dp[l][r] = v[r] - v[l];
            } else {
                dp[l][r] = v[l + 1] - v[l] + v[r] - v[r - 1] + min(dp[l + 2][r - 2],
                                                               min(dp[l + 3][r - 2] + v[l + 2] - v[l + 1],
                                                                   min(dp[l + 2][r - 3] + v[r - 1] - v[r - 2],
                                                                       dp[l + 3][r - 3] + v[l + 2] - v[l + 1] + v[r - 1] - v[r - 2])));
            }
        }
    }
    cout << dp[0][n-1] << "\n";
}