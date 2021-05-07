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

vi prefix(const string &s) {
    vi p(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        int ans = p[i - 1];
        while (s[i] != s[ans] && ans > 0)
            ans = p[ans - 1];
        if (s[i] == s[ans])
            p[i] = ans + 1;
    }
    return p;
}

int main() {
    fast_io

    string s;
    cin >> s;
    vi p = prefix(s);
    int k = s.size() - p[s.size() - 1];
    if (s.size() % k == 0)
        cout << s.size() / k << '\n';
    else
        cout << "1\n";
}