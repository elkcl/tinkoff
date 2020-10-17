#pragma GCC optimize("O3")

#include <iostream>
#include <vector>

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
    vi dp(n+1);
    vi prev(n+1);
    dp[1] = 0;
    prev[1] = -1;
    for (int i = 2; i < n+1; ++i) {
        dp[i] = dp[i-1] + 1;
        prev[i] = 1;
        if (i % 2 == 0 && dp[i/2] + 1 < dp[i]) {
            dp[i] = dp[i/2] + 1;
            prev[i] = 2;
        }
        if (i % 3 == 0 && dp[i/3] + 1 < dp[i]) {
            dp[i] = dp[i/3] + 1;
            prev[i] = 3;
        }
    }
    vi ans;
    int curr = n;
    while (prev[curr] != -1) {
        ans.push_back(prev[curr]);
        switch (prev[curr]) {
            case 1:
                --curr;
                break;
            case 2:
                curr /= 2;
                break;
            case 3:
                curr /= 3;
                break;
        }
    }
    for (int i = static_cast<int>(ans.size()-1); i >= 0; --i) {
        cout << ans[i];
    }
}