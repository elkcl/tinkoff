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
#define file_io(x) freopen((x) + ".in", "r", stdin); freopen((x) + ".out", "w", stdout);

int main() {
    fast_io

    int n;
    string s;
    cin >> n >> s;
    vi suffs(n);
    for (int &el : suffs) {
        cin >> el;
        --el;
    }

    vi ranks(n);
    for (int i = 0; i < n; ++i) {
        ranks[suffs[i]] = i;
    }
    vi lcp(n-1);

    int last = 0;
    for (int i = 0; i < n; ++i) {
        if (last > 0)
            --last;
        if (ranks[i] == n - 1) {
            last = 0;
            continue;
        }
        int j = suffs[ranks[i] + 1];
        while (max(i + last, j + last) < n && s[i + last] == s[j + last])
            ++last;
        lcp[ranks[i]] = last;
    }

    for (int el : lcp)
        cout << el << '\n';
}