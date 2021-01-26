#pragma GCC optimize("O3")

// resend (3)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <deque>
#include <tuple>

using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vll = vector<ll>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);

    int n, m, a1, u1, v1;
    cin >> n >> m >> a1 >> u1 >> v1;
    vi a(n);
    a[0] = a1;
    for (int i = 1; i < n; ++i) {
        a[i] = (23 * a[i-1] + 21'563) % 16'714'589;
    }

    vi logs(n+1, 0);
    logs[1] = 0;
    for (int i = 2; i < n+1; ++i) {
        logs[i] = logs[i / 2] + 1;
    }
    vi tp(logs[n]+1);
    tp[0] = 1;
    for (int i = 1; i < logs[n]+1; ++i) {
        tp[i] = 2 * tp[i-1];
    }
    vvi st(n, vi(logs[n]+1));
    for (int i = 0; i < n; ++i) {
        st[i][0] = a[i];
    }
    for (int j = 1; j < logs[n]+1; ++j) {
        for (int i = 0; i < n - tp[j] + 1; ++i) {
            st[i][j] = min(st[i][j-1], st[i+tp[j-1]][j-1]);
        }
    }

    int uc = min(u1, v1) - 1;
    int vc = max(u1, v1) - 1;
    int k = logs[vc - uc + 1];
    int ans = min(st[uc][k], st[vc - tp[k] + 1][k]);
    for (int i = 2; i <= m; ++i) {
        u1 = ((17 * u1 + 751 + ans + 2*(i-1)) % n) + 1;
        v1 = ((13 * v1 + 593 + ans + 5*(i-1)) % n) + 1;
        uc = min(u1, v1) - 1;
        vc = max(u1, v1) - 1;
        k = logs[vc - uc + 1];
        ans = min(st[uc][k], st[vc - tp[k] + 1][k]);
    }
    cout << u1 << ' ' << v1 << ' ' << ans << '\n';
}

