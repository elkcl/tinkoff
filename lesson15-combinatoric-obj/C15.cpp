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

void gen(vi &v, int n, bool last1 = false, int ind = 0) {
    if (ind == n) {
        for (auto el : v)
            cout << el << ' ';
        cout << '\n';
        return;
    }

    v[ind] = 0;
    gen(v, n, false, ind + 1);
    if (!last1) {
        v[ind] = 1;
        gen(v, n, true, ind + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("fibseq.in", "r", stdin);
    freopen("fibseq.out", "w", stdout);

    int n;
    cin >> n;
    vi v(n);
    gen(v, n);
}