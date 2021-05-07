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
#define file_io(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);

struct Ans {
    ll sum;
    ui mask;
    int popcount;
    bool valid;

    Ans(const vi &a, int n, ui _mask): mask{_mask} {
        sum = popcount = 0;
        for (ui i = 0; i < a.size() * 2; ++i) {
            if (mask & (1u << i)) {
                ++popcount;
                sum += a[i / 2];
            }
        }
        valid = sum == n;
    }

    bool operator<(const Ans &other) const {
        return popcount < other.popcount;
    }
};

int main() {
    fast_io
    file_io("coins")

    int n, m;
    cin >> n >> m;
    vi a(m);
    for (int &el : a)
        cin >> el;
    if (accumulate(all(a), 0) * 2 < n) {
        cout << "-1\n";
        return 0;
    }

    set<Ans> s;
    for (ui mask = 0; mask < (1u << m * 2); ++mask) {
        Ans curr{a, n, mask};
        if (curr.valid)
            s.insert(curr);
    }

    if (s.empty()) {
        cout << "0\n";
        return 0;
    }
    Ans res = *s.begin();
    cout << res.popcount << '\n';
    for (ui i = 0; i < a.size() * 2; ++i) {
        if (res.mask & (1u << i)) {
            cout << a[i / 2] << ' ';
        }
    }
    cout << '\n';
}