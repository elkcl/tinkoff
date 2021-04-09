#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
vector<T> merge(vector<T> &arr, int l1, int r1, int l2, int r2) {
    int len1 = r1 - l1 + 1;
    int len2 = r2 - l2 + 1;
    vector<T> res(len1 + len2);
    int i = l1, j = l2;
    int q = 0;
    while (i <= r1 && j <= r2) {
        if (arr[i] <= arr[j]) {
            res[q] = arr[i];
            ++i;
        } else {
            res[q] = arr[j];
            ++j;
        }
        ++q;
    }
    while (i <= r1) {
        res[q] = arr[i];
        ++i;
        ++q;
    }
    while (j <= r2) {
        res[q] = arr[j];
        ++j;
        ++q;
    }
    return res;
}

template <typename T>
void mergesort(vector<T> &arr, int l, int r) {
    if (l == r) return;
    int m = (l+r)/2;
    mergesort(arr, l, m);
    mergesort(arr, m+1, r);
    vector<T> res = merge(arr, l, m, m+1, r);
    for (int i = 0; i < r-l+1; ++i) {
        arr[l+i] = res[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; ++i) {
        cin >> v[i];
    }
    mergesort(v, 0, n-1);
    for (int i=0; i<n; ++i) {
        cout << v[i] << " ";
    }
}