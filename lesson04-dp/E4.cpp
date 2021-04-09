#pragma GCC optimize("O3")

#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;

int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, n;
    cin >> s >> n;
    vi w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    vi dp(s+1, false);
    dp[0] = true;
    for (int i = 0; i < n; ++i) {
        for (int j = s; j >= 1; --j) {
            if (w[i] <= j) {
                dp[j] = (dp[j] || dp[j - w[i]]);
            }
        }
    }
    for (int j = s; j >= 0; --j) {
        if (dp[j]) {
            cout << j << "\n";
            return 0;
        }
    }
}