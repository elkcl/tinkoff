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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("nextperm.in", "r", stdin);
    freopen("nextperm.out", "w", stdout);

    int n;
    cin >> n;
    vi v(n);
    for (auto &el : v)
        cin >> el;

    if (n == 1) {
        for (auto el : v)
            cout << el << ' ';
        cout << '\n';
        return 0;
    }

    int p1 = n - 2;
    while (v[p1] > v[p1 + 1] && p1 > 0)
        --p1;

    if (v[p1] > v[p1 + 1]) {
        reverse(v.begin(), v.end());
        for (auto el : v)
            cout << el << ' ';
        cout << '\n';
        return 0;
    }

    int p2 = p1 + 1;
    for (int i = p2 + 1; i < n; ++i) {
        if (v[i] > v[p1] && v[i] < v[p2])
            p2 = i;
    }

    swap(v[p1], v[p2]);
    reverse(v.begin()+p1+1, v.end());
    for (auto el : v)
        cout << el << ' ';
    cout << '\n';
}