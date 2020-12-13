#pragma GCC optimize("O3")

#include <iostream>
#include <numeric>
#include <functional>
#include <utility>
//#include <cmath>
//#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;

ll binarySearch(ll lo, ll hi, const function<bool(ll)> &check) {
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

    ll x0, y0, r, x1, y1, x2, y2;
    cin >> x0 >> y0 >> r >> x1 >> y1 >> x2 >> y2;

    ll a = y1 - y2;
    ll b = x2 - x1;
    ll g;
    //ll c;
    //assert(b != 0);
    function<ii(ll)> f;
    if (a == 0) {
        //c = -b * y1;
        f = [x1, y1](ll n) -> ii {
            return {x1 + n, y1};
        };
    } else if (b == 0) {
        //c = -a * x1;
        f = [x1, y1](ll n) -> ii {
            return {x1, y1 + n};
        };
    } else {
        //c = -a * x1 - b * y1;
        g = gcd(a, b);
        if (b > 0) {
            f = [x1, y1, a, b, g](ll n) -> ii {
                return {x1 + n * b / g, y1 - n * a / g};
            };
        } else {
            f = [x1, y1, a, b, g](ll n) -> ii {
                return {x1 - n * b / g, y1 + n * a / g};
            };
        }
    }
    auto inside = [x0, y0, r](ll x, ll y) {
        return (x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r;
    };

    ll lo, hi;
    if (b == 0) {
        lo = binarySearch(-2e8, 2e8, [&f, y0, r](ll k) {
            return f(k).second < y0 - r;
        });
        hi = binarySearch(-2e8, 2e8, [&f, y0, r](ll k) {
            return f(k).second <= y0 + r;
        });
    } else {
        lo = binarySearch(-2e8, 2e8, [&f, x0, r](ll k) {
            return f(k).first < x0 - r;
        });
        hi = binarySearch(-2e8, 2e8, [&f, x0, r](ll k) {
            return f(k).first <= x0 + r;
        });
    }
    //assert(lo <= hi);
    int debugCounter = 0;
    while (!inside(f(lo).first, f(lo).second)) {
        ++lo;
        if (lo > hi) {
            cout << "0\n";
            return 0;
        }
        //assert(debugCounter <= 100);
        ++debugCounter;
    }
    debugCounter = 0;
    while (!inside(f(hi).first, f(hi).second)) {
        --hi;
        //assert(lo <= hi);
        //assert(debugCounter <= 100);
        ++debugCounter;
    }

    cout << hi - lo + 1 << "\n";
}