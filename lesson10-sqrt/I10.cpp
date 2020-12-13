#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    const int C{320};
    int n;
    cin >> n;
    vi a(n);
    vi b(n / C + 1, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > a[b[i / C]]) {
            b[i / C] = i;
        }
    }
    int k;
    cin >> k;
    for (int q = 0; q < k; ++q) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        int ans = l;
        while (l <= r) {
            if (l % C == 0 && l + C - 1 <= r) {
                if (a[b[l / C]] > a[ans]) ans = b[l / C];
                l += C;
            } else {
                if (a[l] > a[ans]) ans = l;
                ++l;
            }
        }
        cout << a[ans] << ' ' << ans + 1 << '\n';
    }
}