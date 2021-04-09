#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
#include <functional>
//#include <numeric>

using namespace std;
using ll = long long;
using vi = vector<ll>;
using ii = pair<ll, ll>;
using vii = vector<ii>;

ll binarySearch(ll lo, ll hi, const function<bool(int)> &check) {
    ll left = lo-1;
    ll right = hi+1;
    while (right - left > 1) {
        ll middle = (left + right) / 2;
        if (check(middle)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi r(n);
    vi b(n);
    //int debug_sum = 0;
    for (int i=0; i<n; ++i) {
        cin >> r[i] >> b[i];
        //debug_sum += r[i];
    }

    vii rs(n);
    for (int i=0; i<n; ++i) {
        rs[i] = {r[i], i};
    }
    sort(rs.begin(), rs.end());
    ll bmax = *max_element(b.begin(), b.end());
    ll cost = binarySearch(0, rs[n-1].first-rs[0].first+bmax, [n, &r, &b, &rs](int x) {
        for (int q=n-1; q>=0; --q) {
            int i = rs[q].second;
            ll k = x - b[i];
            if (b[i] == -1 || k < 0) continue;
            if (k == 0) {
                if (r[i] == rs[n-1].first && r[i] != rs[n-2].first) return false;
                else continue;
            }
            ll ind = lower_bound(rs.begin(), rs.end(), pair{r[i]+k, 0}, [](const ii &a, const ii &b) {
                return a.first < b.first;
            }) - rs.begin();
            ll acc = 0;
            for (int j=ind; j<n; ++j) {
                acc += rs[j].first - r[i] - k + 1;
                if (acc > k) break;
            }
            if (acc <= k) return false;
        }
        return true;
    });
    cout << cost << "\n";
    ll ans, rest, ind;
    bool DEBUG_FLAG = false;
    for (int q=n-1; q>=0; --q) {
        int i = rs[q].second;
        ll k = cost - b[i];
        if (b[i] == -1 || k < 0) continue;
        if (k == 0) {
            if (r[i] == rs[n-1].first && r[i] != rs[n-2].first) {
                DEBUG_FLAG = true;
                ans = i;
                rest = 0;
                break;
            } else continue;
        }
        ind = lower_bound(rs.begin(), rs.end(), pair{r[i]+k, 0}, [](const ii &a, const ii &b) {
            return a.first < b.first;
        }) - rs.begin();
        ll acc = 0;
        for (int j=ind; j<n; ++j) {
            acc += rs[j].first - r[i] - k + 1;
            if (acc > k) break;
        }
        if (acc <= k) {
            DEBUG_FLAG = true;
            ans = i;
            rest = k-acc;
            break;
        }
    }
    assert(DEBUG_FLAG);
    cout << ans+1 << "\n";
    vi rnew(n);
    for (int i=0; i<n; ++i) {
        rnew[i] = r[i];
    }
    ll k = cost - b[ans];
    if (k != 0) {
        rnew[ans] = r[ans] + k;
        for (int j = ind; j < n; ++j) {
            rnew[rs[j].second] = r[ans] + k - 1;
            //acc += max(0, rs[j].first - r[i] - k + 1);
        }
        for (int i=0; i<n; ++i) {
            if (rest == 0) break;
            if (i == ans) continue;
            if (rnew[i] >= rest) {
                rnew[i] -= rest;
                rest = 0;
            } else {
                rest -= rnew[i];
                rnew[i] = 0;
            }
        }
        //if (ind == n) --ind;
        //rnew[rs[ind].second] -= rest;
    }
    //assert(accumulate(r.begin(), r.end(), 0ll) == accumulate(rnew.begin(), rnew.end(), 0ll));
    for (int i=0; i<n; ++i) {
        cout << rnew[i] << " ";
    }

    //assert(debug_acc == debug_sum);
}