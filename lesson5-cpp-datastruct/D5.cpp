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
#include <set>

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
    //freopen("path.in", "r", stdin);
    //freopen("path.out", "w", stdout);

    int n, k, p;
    cin >> n >> k >> p;
    vi zap(p);
    vector<deque<int>> occ(n);
    for (int i = 0; i < p; ++i) {
        cin >> zap[i];
        --zap[i];
        occ[zap[i]].push_back(i);
    }
    set<ii> fl;
    int ans = 0;

    for (int i = 0; i < p; ++i) {
        if () {

        }
    }
}

