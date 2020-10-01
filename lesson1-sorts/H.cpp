#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>


using namespace std;
const int MAXDIFF = 1e7;

template <typename T>
void countSort(vector<T> &arr, int l, int r) {
    int n = r-l+1;
    vector<T> res(n);
    T C_min = arr[l];
    for (int i = 0; i < n; ++i) {
        C_min = min(C_min, arr[l+i]);
    }
    --C_min;
    //const int MAXABS = abs(C-MAXOFFSET);
    vector<T> cnt(MAXDIFF+2, 0);
    vector<T> pref(MAXDIFF+2, 0);
    for (int i = 0; i < n; ++i) {
        ++cnt[arr[l+i]-C_min];
    }
    pref[0] = cnt[0];
    for (int i = 1; i < MAXDIFF+1; ++i) {
        pref[i] = pref[i-1] + cnt[i];
    }
    for (int i = 0; i < n; ++i) {
        res[pref[arr[l+i]-1-C_min]] = arr[l+i];
        ++pref[arr[l+i]-1-C_min];
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