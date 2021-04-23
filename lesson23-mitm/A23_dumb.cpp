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
using ui = unsigned int;

struct Ans {
    ll w;
    ll c;
    ui mask;

    bool operator<(const Ans &other) const {
        return c < other.c;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    /*freopen("dowry.in", "r", stdin);
    freopen("dowry.out", "w", stdout);*/

    int n;
    ll l, r;
    cin >> n >> l >> r;
    vll w(n);
    vll c(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> c[i];
    }
    vector<Ans> pairs;

    for (ui mask = 0; mask < (1 << n); ++mask) {
        ll sum = 0;
        ll weight = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                weight += w[i];
                sum += c[i];
            }
        }
        if (weight >= l && weight <= r)
            pairs.push_back({weight, sum, mask});
    }
    if (pairs.empty()) {
        cout << "0\n";
        return 0;
    }
    ui ans = max_element(pairs.begin(), pairs.end())->mask;
    vi ans_v;
    for (int i = 0; i < n; ++i) {
        if (ans & (1 << i)) {
            ans_v.push_back(i+1);
        }
    }

    //cout << ans.w << ' ' << ans.c << ' ' << ans.mask << '\n';

    cout << ans_v.size() << '\n';
    for (auto el : ans_v)
        cout << el << ' ';
    cout << '\n';
}