#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vc = vector<char>;

int binarySearch(int lo, int hi, const function<bool(int)> &check) {
    int left = lo-1;
    int right = hi+1;
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
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vvi g(n, vi(n));
    int mincap = 1e9;
    int maxcap = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
            if (i != j) {
                mincap = min(mincap, g[i][j]);
                maxcap = max(maxcap, g[i][j]);
            }
        }
    }
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }
    vc used(n, false);
    int usedCount = 0;
    function<void(int, int, bool)> dfs = [&g, &used, &dfs, &usedCount, n](int v, int capacity, bool isTransposed) -> void {
        used[v] = true;
        ++usedCount;
        if (isTransposed) {
            for (int j = 0; j < n; ++j) {
                if (g[j][v] <= capacity && used[j] == 0) {
                    dfs(j, capacity, isTransposed);
                }
            }
        } else {
            for (int j = 0; j < n; ++j) {
                if (g[v][j] <= capacity && used[j] == 0) {
                    dfs(j, capacity, isTransposed);
                }
            }
        }
    };
    int ans = binarySearch(mincap, maxcap, [&used, &usedCount, &dfs, n](int k) {
        fill(used.begin(), used.end(), false);
        usedCount = 0;
        dfs(0, k, false);
        if (usedCount < n) return true;
        fill(used.begin(), used.end(), false);
        usedCount = 0;
        dfs(0, k, true);
        return usedCount < n;
    });
    cout << ans << "\n";
}