#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
using vi = vector<int>;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;

    sort(a.begin(), a.end());
    vi delta(n, 0);
    for (int j = 0; j < q; ++j) {
        int k, x;
        cin >> k >> x;
        delta[n-k] += x;
    }
    for (int i = 1; i < n; ++i) {
        delta[i] += delta[i-1];
    }
    for (int i = 0; i < n; ++i) {
        cout << a[i] + delta[i] << " ";
    }
    cout << "\n";
}