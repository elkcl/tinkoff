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

void gen(vi &v, int rest, int max = -1, int ind = 0) {
    if (max == -1) max = rest;

    if (rest == 0) {
        for (int i = 0; i < ind; ++i) {
            cout << v[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for (int k = 1; k <= min(max, rest); ++k) {
        v[ind] = k;
        gen(v, rest - k, k, ind + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);

    int n;
    cin >> n;
    vi v(n);
    gen(v, n);
}