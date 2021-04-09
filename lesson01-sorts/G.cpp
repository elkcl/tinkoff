#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int MAXABS = 1e4;

template <typename T>
void countSort(vector<T> &arr, int l, int r) {
    int n = r-l+1;
    vector<T> res(n);
    T C = arr[l];
    for (int i = 0; i < n; ++i) {
        C = max(C, arr[l+i]);
    }
    vector<T> cnt(C+MAXABS+1, 0);
    vector<T> pref(C+MAXABS+1, 0);
    for (int i = 0; i < n; ++i) {
        ++cnt[arr[l+i]+MAXABS];
    }
    pref[0] = cnt[0];
    for (int i = 1; i < C+MAXABS+1; ++i) {
        pref[i] += pref[i-1] + cnt[i];
    }
    for (int i = 0; i< n; ++i) {
        res[pref[arr[l+i]-1+MAXABS]] = arr[l+i];
        ++pref[arr[l+i]-1+MAXABS];
    }
    arr = res;
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
    countSort(v, 0, n-1);
    for (int i=0; i<n; ++i) {
        cout << v[i] << " ";
    }
}