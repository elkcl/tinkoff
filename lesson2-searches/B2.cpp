#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using vi = vector<int>;

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
    for (int c1=0; c1<k; ++c1) {
        int q;
        cin >> q;
        int index = binarySearch(0, n-1, [&v, q](int x) {
            return v[x] < q;
        });
        if (index == n) {
            cout << v[n-1] << "\n";
        } else if (index == 0) {
            cout << v[0] << "\n";
        } else if (v[index] == q) {
            cout << q << "\n";
        } else if (q-v[index-1] <= v[index]-q) {
            cout << v[index-1] << "\n";
        } else {
            cout << v[index] << "\n";
        }
    }
}