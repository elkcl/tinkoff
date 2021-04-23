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
    ll s;
    ui mask;

    bool operator<(const Ans &other) const {
        return s < other.s;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vll a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<Ans> pairs;

    for (ui mask = 0; mask < 1u << (n/2); ++mask) {
        ll sum = 0;
        for (int i = 0; i < n/2; ++i) {
            if (mask & (1u << i)) {
                sum = (sum + a[i]) % m;
            }
        }
        pairs.push_back({sum, mask});
    }
    sort(pairs.begin(), pairs.end());

    ll ans = 0;
    int part2_digcount = (n%2 == 0) ? n/2 : n/2+1;
    for (ui mask = 0; mask < (1u << part2_digcount); ++mask) {
        ll sum = 0;
        for (int i = 0; i < part2_digcount; ++i) {
            if (mask & (1u << i)) {
                sum = (sum + a[i + n/2]) % m;
            }
        }
        auto match_it = upper_bound(pairs.begin(), pairs.end(), Ans{m-sum-1, mask});
        if (match_it != pairs.begin()) {
            auto match = *(match_it - 1);
            auto last = *(pairs.end()-1);
            auto max_item = ((match.s + sum) % m > (last.s + sum) % m) ? match : last;
            ans = max(ans, (max_item.s + sum) % m);
        }
    }

    cout << ans << '\n';
}