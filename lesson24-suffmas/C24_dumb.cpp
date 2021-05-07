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
#define file_io(x) freopen((x) + ".in", "r", stdin); freopen((x) + ".out", "w", stdout);

int main() {
    fast_io

    string s;
    ll k;
    cin >> s >> k;
    --k;
    ll n = s.size();

    set<string> subs;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 1; j < n - i + 1; ++j) {
            subs.insert(s.substr(i, j));
        }
    }
    vector<string> sublist;
    copy(all(subs), back_inserter(sublist));
    if (k >= sublist.size()) {
        cout << sublist.back() << '\n';
    } else {
        cout << sublist[k] << '\n';
    }
}