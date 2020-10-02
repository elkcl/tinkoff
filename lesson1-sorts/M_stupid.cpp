//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
typedef int64_t ll;

template <typename T>
int kstat(vector<T> &arr, int l, int r, int k) {
    int ind = (l+r)/2;
    T mid = arr[ind];
    int i = l-1;
    int j = r+1;
    while (true) {
        do {
            ++i;
        } while (arr[i] < mid);
        do {
            --j;
        } while (arr[j] > mid);
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    if (j-l == k-1) {
        return j;
    } else if (j-l > k-1) {
        return kstat(arr, l, j-1, k);
    } else {
        return kstat(arr, j+1, r, k-(j-l)-1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (int i=0; i<n; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    cout << v[k-1] << "\n";
}