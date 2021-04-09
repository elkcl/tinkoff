#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

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
    cin >> n;
    vi v(n);
    for (int i=0; i<n; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    cin >> k;
    for (int c1=0; c1<k; ++c1) {
        int q;
        cin >> q;
        int index1 = binarySearch(0, n-1, [&v, q](int x) {
            return v[x] < q;
        }) - 1; //последний элемент, меньший q
        int index2 = binarySearch(0, n-1, [&v, q](int x) {
            return v[x] <= q;
        }); //первый элемент, больший q
        cout << index2 - index1 - 1 << "\n";
    }
}