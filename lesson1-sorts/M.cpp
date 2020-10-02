#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>
#include <random>

using namespace std;
typedef int64_t ll;

template <typename T>
int kstat(vector<T> &arr, int l, int r, int k) {
    static random_device rd;
    static mt19937 rng(rd());
    uniform_int_distribution<int> gen(l, r);
    int ind = gen(rng);
    swap(arr[ind], arr[r]);

    T pivot = arr[r];
    int i = l;
    for (int j=l; j<=r; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[r]);

    if (i-l == k-1) {
        return i;
    } else if (i-l > k-1) {
        return kstat(arr, l, i-1, k);
    } else {
        return kstat(arr, i+1, r, k-(i-l)-1);
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
    int ans = kstat(v, 0, n-1, k);
    cout << v[ans] << "\n";
}