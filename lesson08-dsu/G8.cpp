#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <map>

using namespace std;
using ld = long double;
using vi = vector<int>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using ii = pair<int, int>;
using vii = vector<ii>;

const ll INF = 1e18;

int main() {
    /*freopen("unionday.in", "r", stdin);
    freopen("unionday.out", "w", stdout);*/
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vll a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<pair<int, int>, ll> sp;
    for (int i = 0; i < m; ++i) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        if (sp.count({x-1, y-1}) == 1) {
            sp[{x-1, y-1}] = sp[{y-1, x-1}] = min(w, sp[{x-1, y-1}]);
        } else {
            sp[{x-1, y-1}] = sp[{y-1, x-1}] = w;
        }
    }
    auto g = [&a, &sp](int i, int j) -> ll {
        if (sp.count({i, j}) == 1) {
            return min(a[i] + a[j], sp[{i, j}]);
        } else {
            return a[i] + a[j];
        }
    };

    ll cost = 0;
    vector<char> used(n, false);
    vector<ll> minW(n, INF);
    vi minWNeigh(n, -1);
    minW[0] = 0;
    for (int q = 0; q < n; ++q) {
        int v = -1;
        for (int i = 0; i < n; ++i) {
            if (!used[i] && (v == -1 || minW[i] < minW[v])) v = i;
        }
        used[v] = true;
        if (minWNeigh[v] != -1) cost += g(v, minWNeigh[v]);
        for (int to = 0; to < n; ++to) {
            if (g(v, to) < minW[to]) {
                minW[to] = g(v, to);
                minWNeigh[to] = v;
            }
        }
    }

    cout << cost << '\n';
}