#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif

#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <numeric>
#include <set>

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
#ifndef ONPC
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#else
#define file_io(x)
#endif

vi z_func(const string &s) {
    int n = static_cast<int>(s.size());
    vi z(s.size(), 0);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

vi a_func(const string &s, const vi &z) {
    int n = static_cast<int>(s.size());
    vi a(s.size(), 0);
    int l = n, r = n;
    for (int i = n - 1; i >= 0; --i) {
        if (i >= l)
            a[i] = min(i - l + 1, z[r - i]);
        while (i - a[i] >= 0 && a[i] < n && s[i - a[i]] == s[a[i]])
            ++a[i];
        if (i - a[i] + 1 < l) {
            l = i - a[i] + 1;
            r = i;
        }
    }
    return a;
}

int main() {
    fast_io

    int n;
    string s;
    cin >> n >> s;
    vi a = a_func(s, z_func(s));
    for (int el : a)
        cout << el << ' ';
    cout << '\n';
}