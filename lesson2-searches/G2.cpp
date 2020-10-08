#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vi v(n);
    for (int i=0; i<n; ++i) {
        cin >> v[i];
    }
    int ans = binarySearch(0, v[n-1]-v[0], [&v, k, n](int x) {
        int left = k-1;
        int last = 0;
        for (int i=1; i<n; ++i) {
            if (v[i] - v[last] >= x) {
                last = i;
                --left;
            }
        }
        return left <= 0;
    }) - 1;
    cout << ans << "\n";
}