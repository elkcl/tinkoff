#pragma GCC optimize("O3")

// resend (3)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <deque>
#include <tuple>
#include <set>
#include <string>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vll = vector<ll>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

const int INF = 1e9;

ll fac(ll x) {
    static unordered_map<ll, ll> s_pred;
    if (x == 0) return 1;
    if (s_pred.count(x) == 1) return s_pred[x];
    return s_pred[x] = x * fac(x-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen("path.in", "r", stdin);
    //freopen("path.out", "w", stdout);

    string s;
    cin >> s;
    vll cnt(26, 0);
    ll len = s.size();
    for (char c : s) {
        ++cnt[c - 'a'];
    }
    ll ans = fac(len);
    for (int i = 0; i < 26; ++i) {
        ans /= fac(cnt[i]);
    }
    cout << ans << '\n';
}

