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
        return w < other.w;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("dowry.in", "r", stdin);
    freopen("dowry.out", "w", stdout);

    int n;
    ll l, r;
    cin >> n >> l >> r;
    vll w(n);
    vll c(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> c[i];
    }
    vector<Ans> pairs;

    for (ui mask = 0; mask < 1u << (n/2); ++mask) {
        ll sum = 0;
        ll weight = 0;
        for (int i = 0; i < n/2; ++i) {
            if (mask & (1u << i)) {
                weight += w[i];
                sum += c[i];
            }
        }
        pairs.push_back({weight, sum, mask});
    }
    sort(pairs.begin(), pairs.end());
    vector<Ans> pairs_new;
    /*Ans last = pairs[0];
    for (auto el : pairs) {
        if (el.w == last.w) {
            if (el.c > last.c) {
                last = el;
            }
        } else {
            pairs_new.push_back(last);
            last = el;
        }
    }
    pairs_new.push_back(last);*/
    ll last = pairs[0].c;
    for (auto el : pairs) {
        if (el.c >= last) {
            last = el.c;
            pairs_new.push_back(el);
        }
    }

    Ans ans{0, 0, 0};
    int part2_digcount = (n%2 == 0) ? n/2 : n/2+1;
    for (ui mask = 0; mask < (1u << part2_digcount); ++mask) {
        ll sum = 0;
        ll weight = 0;
        for (int i = 0; i < part2_digcount; ++i) {
            if (mask & (1u << i)) {
                weight += w[i + n/2];
                sum += c[i + n/2];
            }
        }
        auto match_it = upper_bound(pairs_new.begin(), pairs_new.end(), Ans{r-weight, sum, mask});
        if (match_it != pairs_new.begin() && (match_it - 1)->w + weight >= l) {
            auto match = *(match_it - 1);
            ans = (match.c + sum > ans.c) ? Ans{match.w + weight, match.c + sum, (mask << (n/2)) + match.mask} : ans;
        }
    }

    if (ans.mask == 0) {
        cout << "0\n";
        return 0;
    }

    vi ans_v;
    for (int i = 0; i < n; ++i) {
        if (ans.mask & (1u << i)) {
            ans_v.push_back(i+1);
        }
    }

    //cout << ans.w << ' ' << ans.c << ' ' << ans.mask << '\n';

    cout << ans_v.size() << '\n';
    for (auto el : ans_v)
        cout << el << ' ';
    cout << '\n';
}