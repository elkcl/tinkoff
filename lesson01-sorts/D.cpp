#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
void bubblesort(vector<T> &arr, int l, int r) {
    int n = r-l+1;
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[l+j] > arr[l+j+1]) {
                swap(arr[l+j], arr[l+j+1]);
                flag = true;
            }
        }
        if (!flag) break;
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
    bubblesort(v, 0, n-1);
    for (int i=0; i<n; ++i) {
        cout << v[i] << " ";
    }
}