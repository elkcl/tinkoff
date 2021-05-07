#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using ui = unsigned int;

#define all(x) (x).begin(), (x).end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);

int main() {
    fast_io
    file_io("bynumber")

    int n, k;
    cin >> n >> k;
    vc used(n, false);
    vi comb(n);
    vi fac(n);
    fac[0] = 1;
    for (int i = 1; i < n; ++i) {
        fac[i] = fac[i - 1] * i;
    }
    for (int i = 0; i < n; ++i) {
        int last = -1;
        int c = 0;
        for (int d = 0; d < n; ++d) {
            if (used[d]) continue;
            if (c * fac[n - i - 1] > k) {
                break;
            } else {
                last = d;
            }
            ++c;
        }
        k -= (c - 1) * fac[n - i - 1];
        used[last] = true;
        comb[i] = last;
    }

    for (int el : comb)
        cout << el + 1 << ' ';
    cout << '\n';
}