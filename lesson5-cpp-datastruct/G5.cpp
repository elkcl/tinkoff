#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using ll = long long;
using vi = vector<int>;
using si = stack<int>;

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

    si s;
    int ans = 0;
    for (int i = 0; i < n+1; ++i) {
        while (!s.empty() && h[i] <= s.top()) {
            int last = s.top();
            s.pop();
            if (s.empty()) break;
            ans = max(ans, h[s.top()] * (last - s.top() - 1));
        }
        s.push(i);
    }
    cout << ans << "\n";
}