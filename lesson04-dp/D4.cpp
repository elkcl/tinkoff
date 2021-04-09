#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string s;
    cin >> n >> k >> s;
    vvi dp(n);
    for (int i = 0; i < n; ++i) {
        dp[i].resize(n-i);
        dp[i][0] = k;
    }
    int ans = n;
    for (int l = n-2; l >= 0; --l) {
        for (int r = l+1; r < n; ++r) {
            if (s[l] == s[r]) {
                if (r - l == 1) {
                    dp[l][r-l] = k;
                } else {
                    dp[l][r-l] = dp[l+1][r-1-l-1];
                }
            } else {
                if (r - l == 1) {
                    dp[l][r-l] = k - 1;
                } else {
                    dp[l][r-l] = max(-1, dp[l+1][r-1-l-1] - 1);
                }
            }
            if (dp[l][r-l] != -1) ++ans;
        }
    }
    cout << ans << "\n";
}