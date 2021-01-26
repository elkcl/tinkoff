#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <unordered_set>

using namespace std;
using ld = long double;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

const ld INF = 1e18;

int main() {
    /*freopen("unionday.in", "r", stdin);
    freopen("unionday.out", "w", stdout);*/
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    vii islands(n);
    for (int i = 0; i < n; ++i) {
        cin >> islands[i].first >> islands[i].second;
    }
    cin >> m;
    vector<unordered_set<int>> sp(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        sp[a-1].insert(b-1);
        sp[b-1].insert(a-1);
    }
    auto g = [&islands, &sp](int i, int j) -> ld {
        if (sp[i].count(j) == 1) return 0;
        return sqrt(
                (islands[i].first - islands[j].first)
                * (islands[i].first - islands[j].first)
                + (islands[i].second - islands[j].second)
                  * (islands[i].second - islands[j].second) );
    };

    ld cost = 0;
    vector<char> used(n, false);
    vector<ld> minW(n, INF);
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

    cout.setf(ios::fixed);
    cout.precision(6);
    cout << cost << '\n';
}