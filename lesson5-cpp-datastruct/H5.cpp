#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using ll = long long;
using vi = vector<ll>;
using si = stack<ll>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi h(n+1);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    h[n] = 0;
    vi pref(n);
    pref[0] = h[0];
    for (int i = 1; i < n; ++i) {
        pref[i] = h[i] + pref[i-1];
    }

    si s;
    ll ans = 0;
    for (ll i = 0; i <= n; ++i) {
        while (!s.empty() && h[i] <= h[s.top()]) {
            int ind = s.top();
            s.pop();
            if (!s.empty()) {
                ans = max(ans, h[ind] * (pref[i-1] - pref[s.top()]));
            } else {
                ans = max(ans, h[ind] * pref[i-1]);
            }
        }
        s.push(i);
    }
    cout << ans << '\n';
}