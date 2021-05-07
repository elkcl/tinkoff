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

vi odd_manaker(const string &s) {
    int n = static_cast<int>(s.size());
    vi d(s.size(), 1);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r)
            d[i] = min(r - i + 1, d[r - i + l]);
        while (i + d[i] < n && i - d[i] >= 0 && s[i + d[i]] == s[i - d[i]])
            ++d[i];
        if (i + d[i] - 1 > r) {
            l = i - d[i] + 1;
            r = i + d[i] - 1;
        }
    }
    return d;
}

int main() {
    fast_io

    string s;
    cin >> s;
    string st = "$";
    for (char c : s) {
        st += c;
        st += '$';
    }
    vi d = odd_manaker(st);
    ll ans = 0;
    for (int i = 0; i < d.size(); ++i) {
        if (st[i] == '$')
            ans += (d[i] - 1) / 2;
        else
            ans += d[i] / 2;
    }
    cout << ans << '\n';
}