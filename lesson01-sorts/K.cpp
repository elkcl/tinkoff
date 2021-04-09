#pragma GCC optimize("O3")


#include <iostream>
#include <vector>
#include <utility>

using namespace std;
typedef int64_t ll;

template <typename T>
pair<vector<T>, ll> merge(vector<T> &arr, int l1, int r1, int l2, int r2) {
    int len1 = r1 - l1 + 1;
    int len2 = r2 - l2 + 1;
    vector<T> res(len1 + len2);
    int i = l1, j = l2;
    int q = 0;
    ll sum = 0;
    while (i <= r1 && j <= r2) {
        if (arr[i] <= arr[j]) {
            res[q] = arr[i];
            ++i;
            sum += j-l2;
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
        sum += j-l2;
    }
    while (j <= r2) {
        res[q] = arr[j];
        ++j;
        ++q;
    }
    return {res, sum};
}

template <typename T>
ll mergesort(vector<T> &arr, int l, int r) {
    if (l == r) return 0;
    ll sum = 0;
    int m = (l+r)/2;
    sum += mergesort(arr, l, m);
    sum += mergesort(arr, m+1, r);
    auto mergeRes = merge(arr, l, m, m+1, r);
    vector<T> res = move(mergeRes.first);
    sum += mergeRes.second;
    for (int i = 0; i < r-l+1; ++i) {
        arr[l+i] = res[i];
    }
    return sum;
}

int main() {
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; ++i) {
        cin >> v[i];
    }
    ll ans = mergesort(v, 0, n-1);
    cout << ans;

    fclose(stdin);
    fclose(stdout);
    return 0;
}