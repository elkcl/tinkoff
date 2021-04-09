#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;
using ld = long double;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

const int INF = 1e9;

int main() {
    freopen("unionday.in", "r", stdin);
    freopen("unionday.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vii cities(n);
    for (int i = 0; i < n; ++i) {
        cin >> cities[i].first >> cities[i].second;
    }
    auto g = [&cities](int i, int j) -> ld {
        return sqrt(
            (cities[i].first - cities[j].first)
            * (cities[i].first - cities[j].first)
            + (cities[i].second - cities[j].second)
            * (cities[i].second - cities[j].second) );
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
    cout.precision(5);
    cout << cost << '\n';
}