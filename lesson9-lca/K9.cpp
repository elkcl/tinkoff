#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> l(n);
    l[0] = 0;
    for (int i = 1; i < n; ++i) {
        int inp;
        cin >> inp;
        l[i] = l[inp-1] + 1;
    }
    int x = 0;

    for (int q = 0; q < m; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            if (abs(l[a-1]-l[b-1]) % 2 == 0) {
                cout << x << '\n';
            } else {
                cout << 0 << '\n';
            }
        } else if (t == 2) {
            int inp;
            cin >> inp;
            x ^= inp;
        }
    }

    return 0;
}