#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
void insertionSort(vector<T> &arr, int l, int r) {
    int n = r-l+1;
    for (int i = 1; i < n; ++i) {
        T x = arr[l+i];
        for (int j = 0; j < i; ++j) {
            if (arr[l+j] >= x) {
                for (int k = i; k >= j+1; --k) {
                    swap(arr[l+k], arr[l+k-1]);
                }
                break;
            }
        }
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
    insertionSort(v, 0, n-1);
    for (int i=0; i<n; ++i) {
        cout << v[i] << " ";
    }
}