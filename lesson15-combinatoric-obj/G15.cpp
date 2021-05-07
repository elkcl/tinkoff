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
    //file_io("parens")

    ll n, k;
    cin >> n >> k;
    vc comb(n * 2);
    vector<vector<ll>> vsc(2 * n + 1, vll(2 * n + 1, 0l));
    vsc[0][0] = 1;
    for (int i = 1; i <= n * 2; ++i) {
        vsc[i][0] = vsc[i - 1][1];
        vsc[i][n * 2] = vsc[i - 1][n * 2 - 1];
        for (int j = 1; j < n * 2; ++j) {
            vsc[i][j] = vsc[i - 1][j - 1] + vsc[i - 1][j + 1];
        }
    }
    int bal = 0;

    for (int i = 0; i < n * 2; ++i) {
        if (bal >= 1 && vsc[2 * n - i - 1][bal + 1] <= k) {
            k -= vsc[2 * n - i - 1][bal + 1];
            comb[i] = ')';
            --bal;
        } else {
            comb[i] = '(';
            ++bal;
        }
    }

    if (k > 0) {
        cout << "N/A\n";
        return 0;
    }
    for (char el : comb)
        cout << el;
    cout << '\n';
}