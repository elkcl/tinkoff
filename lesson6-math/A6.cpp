#pragma GCC optimize("O3")

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    if (m == 1) {
        cout << "0\n";
        return 0;
    }
    if (n == 0) {
        cout << "1\n";
        return 0;
    }
    vll dp(n+1);
    dp[0] = dp[1] = 1;
    for (int i = 2; i < n+1; ++i) {
        dp[i] = 0;
        for (int j = 0; j < i; ++j) {
            dp[i] += ((dp[j] * dp[i-j-1]) % m);
            dp[i] %= m;
        }
    }
    cout << dp[n] << "\n";
}