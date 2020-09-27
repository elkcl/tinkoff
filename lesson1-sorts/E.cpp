#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
void selectionsort(vector<T> &arr, int l, int r) {
    int n = r-l+1;
    for (int i = 0; i < n; ++i) {
        int p = i;
        for (int j = i+1; j < n; ++j) {
            if (arr[l+j] < arr[l+p]) p = j;
        }
        T x = arr[l+p];
        for (int j = p; j >= i+1; --j) {
            arr[l+j] = arr[l+j-1];
        }
        arr[l+i] = x;
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
    selectionsort(v, 0, n-1);
    for (int i=0; i<n; ++i) {
        cout << v[i] << " ";
    }
}