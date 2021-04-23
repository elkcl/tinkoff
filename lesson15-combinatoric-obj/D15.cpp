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
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

void gen(vi &v, int n, int k, int max = -1, int ind = 0) {
    if (max == -1) max = n + 1;
    //if (max == 0) return;
    if (ind == k) {
        for (auto el : v)
            cout << el << ' ';
        cout << '\n';
        return;
    }

    for (int j = k-ind; j < max; ++j) {
        v[ind] = j;
        gen(v, n, k, j, ind + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("comb2.in", "r", stdin);
    freopen("comb2.out", "w", stdout);

    int k, n;
    cin >> k >> n;
    vi v(k);
    gen(v, n, k);
}