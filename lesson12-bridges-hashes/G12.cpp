#pragma GCC optimize("O3")

// resend (2)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vll = vector<ll>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

ll mod(ll a, ll b) {
    ll ans = a % b;
    if (ans < 0) ans += b;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vll primes{ 1000000007,
                1000000009,
                1000000021,
                1000000033,
                1000000087,
                1000000093,
                1000000097,
                1000000103,
                1000000123,
                1000000181,
                1000000207,
                1000000223,
                1000000241,
                1000000271,
                1000000289,
                1000000297,
                1000000321,
                1000000349,
                1000000363,
                1000000403,
                1000000409,
                1000000411,
                1000000427,
                1000000433,
                1000000439,
                1000000447,
                1000000453,
                1000000459,
                1000000483,
                1000000513,
                1000000531,
                1000000579,
                1000000607,
                1000000613,
                1000000637,
                1000000663,
                1000000711,
                1000000753,
                1000000787,
                1000000801,
                1000000829,
                1000000861,
                1000000871,
                1000000891,
                1000000901,
                1000000919,
                1000000931,
                1000000933,
                1000000993,
                1000001011,
                1000001021,
                1000001053,
                1000001087,
                1000001099,
                1000001137,
                1000001161,
                1000001203,
                1000001213,
                1000001237,
                1000001263,
                1000001269,
                1000001273,
                1000001279,
                1000001311,
                1000001329,
                1000001333,
                1000001351,
                1000001371,
                1000001393,
                1000001413,
                1000001447,
                1000001449,
                1000001491,
                1000001501,
                1000001531,
                1000001537,
                1000001539,
                1000001581,
                1000001617,
                1000001621,
                1000001633,
                1000001647,
                1000001663,
                1000001677,
                1000001699,
                1000001759,
                1000001773,
                1000001789,
                1000001791,
                1000001801,
                1000001803,
                1000001819,
                1000001857,
                1000001887,
                1000001917,
                1000001927,
                1000001957,
                1000001963,
                1000001969,
                1000002043,
                1000002089 };
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 100);
    int index = dist(mt);
    const ll m = primes[index];
    const ll k = 53;

    string s, t;
    cin >> s >> t;
    int n = s.size();
    int nt = t.size();
    vll h1(n);
    vll h2(nt);
    vll kp(n+1);
    kp[0] = 1;
    h1[0] = mod((s[0] - 'A' + 1), m);
    h2[0] = mod((t[0] - 'A' + 1), m);
    for (int i = 1; i < n; ++i) {
        kp[i] = mod((kp[i-1] * k), m);
        ll c1 = s[i] - 'A' + 1;
        h1[i] = mod((h1[i-1] * k + c1), m);
    }
    for (int i = 1; i < nt; ++i) {
        ll c2 = t[i] - 'A' + 1;
        h2[i] = mod((h2[i-1] * k + c2), m);
    }
    kp[n] = mod((kp[n-1] * k), m);

    auto ss1 = [&h1, &kp, m](int l, int r) -> ll {
        if (l == 0) return h1[r];
        return mod((h1[r] - h1[l-1] * kp[r - l + 1]), m);
    };
    /*auto ss2 = [&h2, &kp, m](int l, int r) -> ll {
        if (l == 0) return h2[r];
        return mod((h2[r] - h2[l-1] * kp[r - l + 1]), m);
    };*/

    for (int i = 0; i < n-nt+1; ++i) {
        if (ss1(i, i+nt-1) == h2[nt-1]) {
            cout << i << ' ';
        }
    }
}