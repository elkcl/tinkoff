#pragma GCC optimize("O3")

// resend (3)

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

const int INF = 1e9;

template<typename Functor>
int binarySearch(int lo, int hi, const Functor& check) {
    int left = lo - 1;
    int right = hi + 1;
    while (right - left > 1) {
        int middle = (left + right) / 2;
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

    int n, a1, k, b, m;
    cin >> n >> a1 >> k >> b >> m;
    vi a(n);
    a[0] = a1;
    for (int i = 1; i < n; ++i) {
        a[i] = (k * a[i-1] + b) % m;
    }

    vi dp(n, INF);
    vi dpi(n, -1);
    vi p(n, -1);
    dp[0] = -INF;
    for (int i = 0; i < n; ++i) {
        int j = binarySearch(1, n-1, [ai = a[i], &dp](int mid) {
           return dp[mid] <= ai;
        });
        if (dp[j-1] < a[i] && a[i] < dp[j]) {
            dp[j] = a[i];
            dpi[j] = i;
            p[i] = dpi[j-1];
        }
    }

    int len = 0;
    for (int i = n-1; i >= 0; --i) {
        if (dp[i] != INF) {
            len = i;
            break;
        }
    }
    cout << len << '\n';
    vi las(len);
    las[len-1] = dpi[len];
    for (int i = len-2; i >= 0; --i) {
        las[i] = p[las[i+1]];
    }
    for (int i = 0; i < len; ++i) {
        cout << a[las[i]] << ' ';
    }
    cout << '\n';
}

